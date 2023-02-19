import sys
import os
import numpy as np
import PIDController
import glob

try:
    sys.path.append(glob.glob('C:/carla/CARLA_0.9.13/WindowsNoEditor/PythonAPI/carla/dist/carla-*%d.%d-%s.egg' % (
        sys.version_info.major,
        sys.version_info.minor,
        'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])
except IndexError:
    pass

import carla
from math import *
from parameter import *


class FinalProject:
    def __init__(self):
        self.client = carla.Client(HOST, PORT)
        self.client.set_timeout(TIMEOUT)
        print('Calra 연결 성공!')
        self.world = self.client.get_world()
        self.blueprint_library = self.world.get_blueprint_library()
        self.actor_list = []

    def get_current_pose(self, vehicle):
        location = vehicle.get_location()
        x = location.x
        y = location.y
        yaw = vehicle.get_transform().rotation.yaw * (np.pi / 180.0)

        return (x, y, yaw)

    def get_current_velocity(self, vehicle):
        vel = vehicle.get_velocity()
        x = vel.x
        y = vel.y
        return sqrt(x * x + y * y)

    def send_control_command(self, vehicle, throttle, steer, brake, hand_brake=False, reverse=False):
        steer_ = np.fmax(np.fmin(steer, 1.0), -1.0)
        throttle_ = np.fmax(np.fmin(throttle, 1.0), 0)
        brake_ = np.fmax(np.fmin(brake, 1.0), 0)
        vehicle.apply_control(carla.VehicleControl(
            throttle=throttle_, steer=steer_, brake=brake_))

    def run(self):
        # =============================
        # 차량 생성 및 웨이포인트 불러오기
        bp = self.blueprint_library.filter('model3')[0]
        spawn_point = carla.Transform(carla.Location(x=-30.912139, y=-61.104893, z=4.001863),
                                      carla.Rotation(pitch=-0.003265, yaw=0.552418, roll=-0.000763))
        self.vehicle = self.world.spawn_actor(bp, spawn_point)
        self.actor_list.append(self.vehicle)

        import re
        waypoints_np = None
        waypoints = []
        waypoints_file = open(WAYPOINTS_FILENAME, "r")
        for line in waypoints_file:
            temp = []
            cnt = 0
            for element in re.split('[\t\n]', line):
                if element != '' and cnt != 0:
                    temp.append(float(element))
                cnt += 1
            waypoints.append(temp)
        waypoints_file.close()

        waypoints_np = np.array(waypoints)
        for i in waypoints:
            location = carla.Location(x=i[0], y=i[1])
            self.world.debug.draw_point(
                location, size=0.1, life_time=TOTAL_RUN_TIME)
        # 차량 생성 및 웨이포인트 불러오기
        # =============================

        # 웨이 포인트 사이에 선형 보간법으로 새로운 웨이포인트 추가
        wp_distance = []  # distance array

        # waypoints.txt의 행갯수 만큼 반복문 돌리기
        for i in range(1, waypoints_np.shape[0]):
            # 이전 행과 현재 행 사이의 Euclidean distance 구하기
            wp_distance.append(np.sqrt((waypoints_np[i, 0] - waypoints_np[i - 1, 0]) ** 2 +
                                       (waypoints_np[i, 1] - waypoints_np[i - 1, 1]) ** 2))
        wp_distance.append(0)  # 마지막 웨이포인트에서는 웨이포인트 사이 거리가 0임을 넣어줌

        # 웨이 포인트 사이에 선형 보간법으로 새로운 웨이포인트 추가
        wp_interp = []  # 보간된 waypoint 리스트
        wp_interp_hash = []  # 보간된 waypoint의 인덱스 리스트
        interp_counter = 0  # 보간된 포인트의 인덱스 카운트

        for i in range(waypoints_np.shape[0] - 1):
            wp_interp.append(list(waypoints_np[i]))
            wp_interp_hash.append(interp_counter)
            interp_counter += 1

            num_pts_to_interp = int(
                np.floor(wp_distance[i] / float(INTERP_DISTANCE_RES)) - 1)
            wp_vector = waypoints_np[i + 1] - waypoints_np[i]
            wp_uvector = wp_vector / np.linalg.norm(wp_vector)
            for j in range(num_pts_to_interp):
                next_wp_vector = INTERP_DISTANCE_RES * \
                    float(j + 1) * wp_uvector
                wp_interp.append(list(waypoints_np[i] + next_wp_vector))
                interp_counter += 1

        # 마지막 웨이포인트 추가
        wp_interp.append(list(waypoints_np[-1]))  # 보간된 웨이포인트 셋
        wp_interp_hash.append(interp_counter)  # 보간된 인덱스 셋
        interp_counter += 1

        """****************** PID 컨트롤러 인스턴스 생성 ******************"""
        controller = PIDController.PIDController(waypoints)

        num_iterations = ITER_FOR_SIM_TIMESTEP
        if (ITER_FOR_SIM_TIMESTEP < 1):
            num_iterations = 1

        self.world.tick()
        sim_start_stamp = self.world.get_snapshot().elapsed_seconds

        self.send_control_command(
            self.vehicle, throttle=0.0, steer=0, brake=1.0)

        # 시뮬레이션 상의 시간 단위를 구하기 위한 과정
        sim_duration = 0
        for i in range(num_iterations):
            self.send_control_command(
                self.vehicle, throttle=0.0, steer=0, brake=1.0)
            # 마지막 시간 구하기
            if i == num_iterations - 1:
                self.world.tick()
                elapsed = self.world.get_snapshot().elapsed_seconds
                sim_duration = elapsed - sim_start_stamp

        # 위 for문에서 루프 반복 수에 따른 평균 시간 구하기
        SIMULATION_TIME_STEP = sim_duration / float(num_iterations)

        TOTAL_EPISODE_FRAMES = int(
            (TOTAL_RUN_TIME + WAIT_TIME_BEFORE_START) / SIMULATION_TIME_STEP) + TOTAL_FRAME_BUFFER

        start_x, start_y, start_yaw = self.get_current_pose(self.vehicle)
        self.send_control_command(
            self.vehicle, throttle=0.0, steer=0, brake=1.0)
        self.x_history = [start_x]
        self.y_history = [start_y]
        self.yaw_history = [start_yaw]
        self.time_history = [0]
        self.speed_history = [0]

        reached_the_end = False
        closest_index = 0

        for frame in range(TOTAL_EPISODE_FRAMES):
            print("시나리오 진행: ", frame, "/", TOTAL_EPISODE_FRAMES)
            current_x, current_y, current_yaw = self.get_current_pose(
                self.vehicle)
            current_speed = self.get_current_velocity(self.vehicle)
            self.world.tick()
            current_timestamp = self.world.get_snapshot().elapsed_seconds

            # 시뮬레이션 시작 전 대기할 때 차량 제어
            if current_timestamp <= WAIT_TIME_BEFORE_START:
                self.send_control_command(
                    self.vehicle, throttle=0.0, steer=0, brake=1.0)
                continue
            else:
                current_timestamp = current_timestamp - WAIT_TIME_BEFORE_START

            self.x_history.append(current_x)
            self.y_history.append(current_y)
            self.yaw_history.append(current_yaw)
            self.speed_history.append(current_speed)
            self.time_history.append(current_timestamp)

            # 현재 위치를 기준으로 가장 가까운 waypoint의 인덱스(closest_distance)를 구하는 과정
            closest_distance = np.linalg.norm(
                np.array([waypoints_np[closest_index, 0] - current_x, waypoints_np[closest_index, 1] - current_y]))
            new_distance = closest_distance
            new_index = closest_index
            got_it = False
            distance_prev = np.linalg.norm(
                np.array([waypoints_np[closest_index, 0] - current_x, waypoints_np[closest_index, 1] - current_y])) + DISTANCE_OFFSET

            while got_it != True:
                new_index += 1
                new_distance = np.linalg.norm(
                    np.array([waypoints_np[new_index, 0] - current_x, waypoints_np[new_index, 1] - current_y]))
                if new_distance > distance_prev:
                    got_it = True
                    closest_index = new_index
                else:
                    distance_prev = new_distance

            waypoint_subset_first_index = closest_index - 1
            if waypoint_subset_first_index < 0:
                waypoint_subset_first_index = 0

            waypoint_subset_last_index = closest_index
            total_distance_ahead = 0
            while total_distance_ahead < INTERP_LOOKAHEAD_DISTANCE:
                total_distance_ahead += wp_distance[waypoint_subset_last_index]
                waypoint_subset_last_index += 1
                if waypoint_subset_last_index >= waypoints_np.shape[0]:
                    waypoint_subset_last_index = waypoints_np.shape[0] - 1
                    break
            

            new_waypoints = wp_interp[wp_interp_hash[waypoint_subset_first_index]: wp_interp_hash[waypoint_subset_last_index] + 1]
            
            controller.update_waypoints(new_waypoints) # 시뮬레이션 상에서 새로생긴 파란색 웨이포인트

            for i in new_waypoints: # 파란색 웨이포인트 그리기
                location = carla.Location(x=i[0], y=i[1])
                self.world.debug.draw_point(
                    location, size=0.1, color=carla.Color(0, 0, 255), life_time=0.1)

            controller.update_values(
                current_x, current_y, current_yaw, current_speed, current_timestamp, frame)
            controller.update_controls()
            cmd_throttle, cmd_steer, cmd_brake = controller.get_commands()

            self.send_control_command(
                self.vehicle, throttle=cmd_throttle, steer=cmd_steer, brake=cmd_brake)

            dist_to_last_waypoint = np.linalg.norm(
                np.array([waypoints[-1][0] - current_x, waypoints[-1][1] - current_y]))
            if dist_to_last_waypoint < DIST_THRESHOLD_TO_LAST_WAYPOINT:
                reached_the_end = True
                print("시뮬레이션 종료!")
            if reached_the_end:
                break
            #==============================

    def write_log_data(self):
        location_file = open("location_output.txt", 'w')
        for i in range(len(self.x_history)):
            line = [str(self.x_history[i]), "\t", str(self.y_history[i]), "\n"]
            location_file.writelines(line)
        location_file.close()

        velocity_file = open("velocity_output.txt", 'w')
        for i in range(len(self.x_history)):
            line = [str(self.speed_history[i]), "\n"]
            velocity_file.writelines(line)
        velocity_file.close()

    def __del__(self):
        self.client.apply_batch([carla.command.DestroyActor(x)
                                for x in self.actor_list])


def main():
    fp = FinalProject()
    fp.run()
    fp.write_log_data()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nCancelled by user. Bye!')
