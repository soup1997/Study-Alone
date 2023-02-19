import glob
import os
import sys
import time

try:
    sys.path.append(glob.glob('C:/Carla/WindowsNoEditor/PythonAPI/carla/dist/carla-*%d.%d-%s.egg' % (
        sys.version_info.major,
        sys.version_info.minor,
        'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])
except IndexError:
    pass
import carla
import random
from parameters import *
from callback import *
from datetime import datetime

class CarlaTutorial:
    def __init__(self):
        self.actor_list = []
        self.client = carla.Client(HOST, PORT)
        self.client.set_timeout(TIMEOUT)
        print("Carla 접속 성공!")
        self.world = self.client.get_world()
        self.blueprint_library = self.world.get_blueprint_library()
        self.delta = 0.05
        self.setting()

    def setting(self):
        settings = self.world.get_settings()
        self.settings_backup = settings
        settings.fixed_delta_seconds = self.delta
        settings.synchronous_mode = True
        # settings.no_rendering_mode = False
        self.world.apply_settings(settings)


    def setMap(self):
        self.client.load_world(MAP)
        self.client.reload_world()

    def setWeather(self):

        self.world.set_weather(carla.WeatherParameters.Default)

        # weather = carla.WeatherParameters(cloudiness=CLOUD, wind_intensity=WIND, sun_altitude_angle=SUN_ALTI)
        # self.world.set_weather(weather)

    def vehicleSpwan(self):
        bp_vehicle = random.choice(self.blueprint_library.filter('vehicle'))
        self.transform_vehicle = random.choice(self.world.get_map().get_spawn_points())
        self.vehicle = self.world.spawn_actor(bp_vehicle, self.transform_vehicle)
        self.actor_list.append(self.vehicle)
        self.vehicle.set_autopilot(True)
        # self.vehicle.apply_control(carla.VehicleControl(throttle=1.0, steer=0.0))

    def pedestrianSpawn(self):
        self.world.set_pedestrians_seed(1235)
        ped_bp = random.choice(self.world.get_blueprint_library().filter("walker.pedestrian.*"))
        self.trans =random.choice(self.world.get_map().get_spawn_points())
        ped = self.world.spawn_actor(ped_bp, self.trans)
        walker_controller_bp = self.world.get_blueprint_library().find('controller.ai.walker')
        controller = self.world.spawn_actor(walker_controller_bp, carla.Transform(), ped)
        controller.start()
        controller.go_to_location(self.world.get_random_location_from_navigation())
        controller.set_max_speed(1.7)
        self.actor_list.append(controller)
        self.actor_list.append(ped)

    def gnssSpawn(self):
        gnss_bp = self.blueprint_library.find("sensor.other.gnss")
        gnss_transform = carla.Transform(carla.Location(x=1.5, y=2.4))
        # gnss_bp.set_attribute("noise_lon_bias", str(0.00001))
        # gnss_bp.set_attribute("noise_lon_stddev", str(0.00001))
        # gnss_bp.set_attribute("noise_lat_bias", str(0.00001))
        # gnss_bp.set_attribute("noise_lat_stddev", str(0.00001))

        ego_gnss = self.world.spawn_actor(gnss_bp, gnss_transform, attach_to=self.vehicle)
        ego_gnss.listen(lambda gnss:gnss_callback(gnss, self.vehicle))
        self.actor_list.append(ego_gnss)

    def IMUSpawn(self):
        imu_bp = self.blueprint_library.find("sensor.other.imu")
        imu_transform = carla.Transform(carla.Location(x = 1.5, z = 1.4))
        ego_imu = self.world.spawn_actor(imu_bp, imu_transform, attach_to=self.vehicle)
        ego_imu.listen(lambda imu:imu_callback(imu,self.vehicle))
        self.actor_list.append(ego_imu)

    def cameraSpawn(self):
        spawn_point = carla.Transform(carla.Location(x=2.5, z=2.7))
        # cam_bp = self.blueprint_library.find("sensor.camera.rgb")
        # cam_bp = self.blueprint_library.find("sensor.camera.semantic_segmentation")
        cam_bp = self.blueprint_library.find("sensor.camera.instance_segmentation")

        cam_bp.set_attribute("image_size_x", f"{IM_WIDTH}")
        cam_bp.set_attribute("image_size_y", f"{IM_HEIGHT}")
        cam_bp.set_attribute("fov", "110")
        cam_bp.set_attribute("sensor_tick", str(0.5))
        camera = self.world.spawn_actor(cam_bp, spawn_point, attach_to=self.vehicle)
        self.actor_list.append(camera)

        cc = carla.ColorConverter.Raw
        # cc = carla.ColorConverter.LogarithmicDepth
        # cc = carla.ColorConverter.Depth
        # cc = carla.ColorConverter.CityScapesPalette
        #
        # camera.listen(lambda image: image.save_to_disk('_out/%06d.png'%image.frame, cc))
        camera.listen(lambda image: camera_callback(image))

    def lidarSpawn(self):
        spawn_point = carla.Transform(carla.Location(x=0.5, z=1.8))
        lidar_bp = self.blueprint_library.find("sensor.lidar.ray_cast")
        lidar_bp.set_attribute('upper_fov', str(15))
        lidar_bp.set_attribute('lower_fov', str(-25))
        lidar_bp.set_attribute('channels', str(64))
        lidar_bp.set_attribute('range', str(100))
        lidar_bp.set_attribute('rotation_frequency', str(1.0 / self.delta))
        lidar_bp.set_attribute('points_per_second', str(500000))

        lidar = self.world.spawn_actor(lidar_bp, spawn_point, attach_to=self.vehicle)
        self.actor_list.append(lidar)

        point_list = o3d.geometry.PointCloud()


        lidar.listen(lambda data:lidar_callback(data, point_list))

        vis = o3d.visualization.Visualizer()
        vis.create_window(
            window_name='Carla Lidar',
            width=960,
            height=540,
            left=480,
            top=270)
        vis.get_render_option().background_color = [0.1, 0.1, 0.1]
        vis.get_render_option().point_size = 1
        vis.get_render_option().show_coordinate_frame = True

        frame = 0
        dt0 = datetime.now()
        while True:
            if frame == 2:
                vis.add_geometry(point_list)
            vis.update_geometry(point_list)

            vis.poll_events()
            vis.update_renderer()
            # # This can fix Open3D jittering issues:
            time.sleep(0.005)
            self.world.tick()

            process_time = datetime.now() - dt0
            sys.stdout.write('\r' + 'FPS: ' + str(1.0 / process_time.total_seconds()))
            sys.stdout.flush()
            dt0 = datetime.now()
            frame += 1
            self.setSpectator()

    def npcSpawn(self):
        idx = 0
        for _ in range(0, 10):
            npc_transform = random.choice(self.world.get_map().get_spawn_points())
            npc_transform.location.x += 8.0
            bp = random.choice(self.blueprint_library.filter('vehicle'))
            npc = self.world.try_spawn_actor(bp, npc_transform)

            if npc is not None:
                idx += 1
                self.actor_list.append(npc)
                npc.set_autopilot(True)


    def setSpectator(self):
        spectator = self.world.get_spectator()
        transform = self.vehicle.get_transform()
        tr = carla.Transform(carla.Location(x=transform.location.x, y=transform.location.y, z=2.5), \
                             carla.Rotation(pitch=transform.rotation.pitch, yaw=transform.rotation.yaw, roll=transform.rotation.roll))
        spectator.set_transform(tr)
        # spectator.set_transform(self.trans)

    def __del__(self):
        self.world.apply_settings(self.settings_backup)
        self.client.apply_batch([carla.command.DestroyActor(x) for x in self.actor_list])

def main():
    tutorial = CarlaTutorial()
    # tutorial.setMap()
    # tutorial.setWeather()
    tutorial.vehicleSpwan()
    # tutorial.IMUSpawn()
    # tutorial.gnssSpawn()
    # tutorial.pedestrianSpawn()
    # tutorial.npcSpawn()
    # tutorial.cameraSpawn()
    tutorial.setSpectator()
    tutorial.lidarSpawn()


    time.sleep(100)


if __name__ == '__main__':

    try:
        main()
    except KeyboardInterrupt:
        print("end")
