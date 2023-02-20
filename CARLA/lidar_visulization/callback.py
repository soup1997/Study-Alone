from parameters import  *
from math import *
import numpy as np
import cv2
import open3d as o3d

def lidar_callback(point_cloud, point_list):
    data = np.copy(np.frombuffer(point_cloud.raw_data, dtype=np.dtype('f4')))
    data = np.reshape(data, (int(data.shape[0] / 4), 4))

    points = data[:, :-1]

    points[:,:1] = -points[:,:1]
    point_list.points = o3d.utility.Vector3dVector(points)


def camera_callback(image):
    i = np.array(image.raw_data)
    i2 = i.reshape(IM_HEIGHT, IM_WIDTH, 4)
    i3 = i2[:, :, :3]
    cv2.imshow("", i3)
    cv2.waitKey(1)


def imu_callback(imu, vehicle):
    print("IMU Measure: \n" + str(imu) + "\n")
    print("get_acceleration():", vehicle.get_acceleration())
    print("get_angular_velocity():", vehicle.get_angular_velocity())

def gnss_callback(gnss, vehicle):
    print("GNSS measure:\n" + str(gnss) + '\n')
    print(gnss.latitude, " ", gnss.longitude)  # 위도(latitude), 경도(longitude)
    lat = gnss.latitude
    lon = gnss.longitude
    alt = gnss.altitude
    radius = (EARTH_RADIUS_MAJOR * EARTH_RADIUS_MAJOR) / sqrt( \
        EARTH_RADIUS_MAJOR * EARTH_RADIUS_MAJOR * cos(lat * drad) * cos( \
            lat * drad) + EARTH_RADIUS_MAJOR * EARTH_RADIUS_MAJOR * sin(lat * drad) * sin(lat * drad)) + alt
    # print("lat, lon, alt", lat, lon, alt)
    global CNT
    CNT += 1
    if CNT == 1:
        global INIT_LAT
        global INIT_LON
        global INIT_ALT
        init_location = vehicle.get_location()
        x = init_location.x
        y = init_location.y
        z = init_location.z

        INIT_LAT = lat + y / (radius * drad)
        INIT_LON = lon - x / (radius * drad * cos(INIT_LAT * drad))
        INIT_ALT = alt - z

    print("vehicle pose : ", vehicle.get_transform())
    x_gt = vehicle.get_location().x
    y_gt = vehicle.get_location().y

    x = radius * (lon - INIT_LON) * drad * cos(INIT_LAT * drad)
    y = radius * ((-lat + INIT_LAT) * drad)
    z = alt - INIT_ALT
    print("x, y, z: ", x, y, z)