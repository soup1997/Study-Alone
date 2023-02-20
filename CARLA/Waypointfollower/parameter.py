# Carla 접속 파라미터
HOST = 'localhost'
PORT = 2000
TIMEOUT = 10.0

# 시뮬레이션 시작 파라미터
ITER_FOR_SIM_TIMESTEP = 10
WAIT_TIME_BEFORE_START = 5.00
TOTAL_RUN_TIME = 200.00
TOTAL_FRAME_BUFFER = 300  # 시뮬레이션 종류 후 더 진행될 프레임 수

# 시뮬레이션 종료 파라미터
DIST_THRESHOLD_TO_LAST_WAYPOINT = 2.0  # 종료 위치에서 떨어진 거리
WAYPOINTS_FILENAME = "waypoints.txt"  # waypoint 파일

# lookahead 경로
INTERP_LOOKAHEAD_DISTANCE = 30  # lookahead 거리, waypoint subset의 길이
INTERP_DISTANCE_RES = 0.1   # 보간된 waypoint간 사이 거리
DISTANCE_OFFSET = 2         # 근접 waypoint를 찾을 때, 차량의 이동을 고려해 현재 위치보다 더 먼