import sys
import os
import numpy as np
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


class FinalProject:
    def __init__(self, xodr_file, xosc_file):
        self.client = carla.Client(HOST, PORT)
        self.client.set_timeout(TIMEOUT)
        print('Calra 연결 성공!')
        
        self.get_xord(xodr_file)

        self.blueprint_library = self.world.get_blueprint_library()
        self.actor_list = []

    def get_xord(self, xodr_file):
        with open(xodr_file, 'r') as od_file:
            data = od_file.read()

        index = data.find('<OpenDRIVE>')
        data = data[index:]

        vertex_distance = 2.0  # in meters
        wall_height = 1.0      # in meters
        extra_width = 0.6      # in meters

        self.world = self.client.generate_opendrive_world(str(data),
                                                                 carla.OpendriveGenerationParameters(
                                                                 vertex_distance=vertex_distance,
                                                                 wall_height=wall_height,
                                                                 additional_width=extra_width,
                                                                 smooth_junctions=True,
                                                                 enable_mesh_visibility=True))

    def __del__(self):
        self.client.apply_batch([carla.command.DestroyActor(x)
                                for x in self.actor_list])


def main():
    fp = FinalProject('E:/로드밸런싱/Map_Test/sample_senario/Road_1_sample.xodr')

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nCancelled by user. Bye!')
