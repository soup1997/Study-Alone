#!/usr/bin/env python3

import carla
from math import *
import sys
import os
import glob
import parameters as p


class Project:
    def __init__(self, HOST, PORT, TIMEOUT):

        try:
            sys.path.append(glob.glob('/home/smeet/Desktop/Carla/CARLA_0.9.13/PythonAPI/carla/dist/carla-*%d.%d-%s.egg' % (
                sys.version_info.major,
                sys.version_info.minor,
                'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])

        except IndexError:
            pass

        self.client = carla.Client(HOST, PORT)
        self.client.set_timeout(TIMEOUT)
        print('Connection Complete', end="\n")

        # os.system('/home/smeet/Desktop/Carla/CARLA_0.9.13/CarlaUE4.sh')

    def get_xord(self, xodr_file):
        with open(xodr_file, 'r') as od_file:
            xodr = od_file.read()

        index = xodr.find('<OpenDRIVE>')
        xodr = xodr[index:]

        self.world = self.client.generate_opendrive_world(str(xodr),
                                                          carla.OpendriveGenerationParameters(
            vertex_distance=p.vertex_distance,
            wall_height=p.wall_height,
            additional_width=p.extra_width,
            smooth_junctions=p.smooth_junctions,
            enable_mesh_visibility=p.enable_mesh_visibility,
            enable_pedestrian_navigation=p.enable_pedestrian_navigation))

    def traffic_control(self):
        states = [carla.TrafficLightState.Red, carla.TrafficLightState.Yellow,
                  carla.TrafficLightState.Green, carla.TrafficLightState.Off]

        for tl in self.world.get_actors().filter('traffic.traffic_light'):
            print("Traffic Light: {}".format(tl))

            if isinstance(tl, carla.TrafficLight):

                affected_waypoints = tl.get_affected_lane_waypoints()

                for waypoints in affected_waypoints:
                    point = waypoints.transform.location
                    location = carla.Location(x=point.x, y=point.y)

                    self.world.debug.draw_point(
                        location, size=0.2, color=carla.Color(255, 0, 0), life_time=-1)

                for traffic_state in states:

                    tl.set_state(traffic_state)

                    if traffic_state == carla.TrafficLightState.Red:
                        tl.set_red_time(4.0)

                    elif traffic_state == carla.TrafficLightState.Yellow:
                        tl.set_yellow_time(4.0)

                    elif traffic_state == carla.TrafficLightState.Green:
                        tl.set_green_time(4.0)

                    else:
                        break

    def main(self):
        self.get_xord(xodr_file='./Road_1_sample.xodr')
        self.traffic_control()


if __name__ == '__main__':
    try:
        car = Project(HOST='localhost', PORT=2000, TIMEOUT=10.0)
        car.main()

    except KeyboardInterrupt:
        print('\nCancelled by user!')
