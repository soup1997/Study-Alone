import numpy as np
from parameter import *
from math import *


class PIDController(object):
    def __init__(self, waypoints):
        self._current_x = 0
        self._current_y = 0
        self._current_yaw = 0

        self._current_speed = 0
        self._desired_speed = 0
        self._current_frame = 0

        self._current_timestamp = 0

        self._start_control_loop = False

        self._set_throttle = 0
        self._set_brake = 0
        self._set_steer = 0
        self._waypoints = waypoints

        self._conv_rad_to_steer = 180.0 / 70.0 / np.pi
        self._pi = np.pi
        self._2pi = 2.0 * np.pi
        self.v_prev = 0
        self.t_prev = 0
        self.e_prev = 0
        self.e_iprev = 0
        self.o_tprev = 0
        self.o_sprev = 0

        # PID제어 파라미터
        self.Kp = 1.2
        self.Ki = 0.2
        self.Kd = 0.02

        # Pure Pursuit 파라미터
        self.model3_wheelbase = 2.875  # 2.875 meter
        self.ld = 0.0

    def update_values(self, x, y, yaw, speed, timestamp, frame):
        self._current_x = x
        self._current_y = y
        self._current_yaw = yaw
        self._current_speed = speed

        self._current_timestamp = timestamp

        self._current_frame = frame
        if self._current_frame:
            self._start_control_loop = True

    def update_desired_speed(self):
        min_idx = 0
        min_dist = float("inf")
        desired_speed = 0
        for i in range(len(self._waypoints)):
            
            # 현재 위치와 모든 waypoint간의 거리 구하기
            dist = np.linalg.norm(
                np.array([self._waypoints[i][0] - self._current_x, self._waypoints[i][1] - self._current_y]))
            
            # minimum 거리값 찾기
            if dist < min_dist:
                min_dist = dist
                min_idx = i

        if min_idx < len(self._waypoints) - 1:
            desired_speed = self._waypoints[min_idx][2]
        
        else:
            desired_speed = self._waypoints[-1][2]
        self._desired_speed = desired_speed

    def update_waypoints(self, new_waypoints):
        self._waypoints = new_waypoints

    def get_commands(self):
        return self._set_throttle, self._set_steer, self._set_brake

    def set_throttle(self, input_throttle):
        # 1.0~0.0 사이값 출력
        throttle = np.fmax(np.fmin(input_throttle, 1.0), 0.0)
        self._set_throttle = throttle

    def set_steer(self, input_steer_in_rad):
        input_steer = self._conv_rad_to_steer * input_steer_in_rad

        # -1~1 [rad] 값으로 변환
        steer = np.fmax(np.fmin(input_steer, 1.0), -1.0)
        self._set_steer = steer

    def set_brake(self, input_brake):
        # 0.0 ~ 1.0 사이값 출력
        brake = np.fmax(np.fmin(input_brake, 1.0), 0.0)
        self._set_brake = brake

    def update_controls(self):
        x = self._current_x  # meter
        y = self._current_y  # meter
        yaw = self._current_yaw  # radian
        v = self._current_speed  # m/s
        self.update_desired_speed()
        v_desired = self._desired_speed  # m/s

        t = self._current_timestamp
        waypoints = self._waypoints  # x, y, v
        throttle_output = 0  # 0~1
        steer_output = 0  # -1.22~1.22(rad)
        i_v = 0

        if self._start_control_loop:
            # TODO 1: *********** 종방향 제어기(Longitudinal controller) 설계 (PID 제어기) ***********
            dt = t - self.t_prev
            error = v_desired - v
            i_v = (self.e_iprev + error) * dt

            p_control = self.Kp * error
            i_control = self.Ki * i_v
            d_control = self.Kd * ((error - self.e_prev) / dt)
            throttle_output = p_control + i_control + d_control
            
            if throttle_output > 0:
                throttle_output = (np.tanh(throttle_output) + 1) / 2
                print(throttle_output)
                self.set_throttle(throttle_output)
            
            else:
                throttle_output = 0

            # TODO 2: *********** 횡방향 제어기 (Lateral controller) 설계 - [ PurePursuit ] ***********
            xc = x - self.model3_wheelbase*cos(yaw) # 후륜 중심점 x좌표
            yc = y - self.model3_wheelbase*sin(yaw) # 후륜 중심점 y좌표

            ld = sqrt((waypoints[0][1] - yc)**2 + (waypoints[0][0] - xc)**2)
            alpha = atan2(waypoints[0][1] - yc, waypoints[0][0] - xc) - yaw
            steer_output = atan2(2*self.model3_wheelbase*sin(alpha), ld)
            
            self.set_steer(steer_output)

        self.v_prev = v
        self.t_prev = t
        self.e_prev = v_desired - v
        self.e_iprev = i_v
        self.o_tprev = throttle_output
        self.o_sprev = steer_output

