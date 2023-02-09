# Study-Alone
매일 공부하는 것을 기록하고 정리하기 위한 레포지토리

## MATLAB/Simulink(📊) , Deep Learning(🧬), Troubleshooting(✔), Data Structure(🛢), C++, Concept(🙄)
### 2023年
1/8   
🔹 MATLAB Onramp 수료 🏆    
***
1/13      
🔹 [Average Filter(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Average_Filter)   
🔹 [Average Filter 정리](https://velog.io/@soup1997/%ED%8F%89%EA%B7%A0%ED%95%84%ED%84%B0)   
🔹 [Moving Average Filter(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Moving_Average_Filter)   
🔹 [Moving Average Filter 정리](https://velog.io/@soup1997/Moving-Average-Filter)  
***
1/16     
🔹 [Lowpass Filter(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Lowpass_Filter)   
🔹 [Lowpass Filter 정리](https://velog.io/@soup1997/Lowpass-Filter)   
***
1/26     
🔹 [Kalman Filter 정리](https://velog.io/@soup1997/Linear-Kalman-Filter)   
***
1/27    
🔹 Simulink Onramp 수료 🏆   
🔹 [Kalman Filter(Simple example)(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab)   
🔹 [Kalman Filter 정리(Simple example)](https://velog.io/@soup1997/Linear-Kalman-Filter-Simple-Example)   
🔹 [PI Controller(Simulink)](https://github.com/soup1997/Study-Alone/tree/origin/Simulink)   
🔹 Difference between 'purge' and 'remove'(Linux)   
>`$ sudo apt remove package_name`   
>`$ sudo apt purge package_name`    
>Both apt-remove and apt-purge do the same thing and that is to uninstall a package. The apt-purge removes the package and purges any configuration files associated with it. That’s the only difference between the two.   

🔹 [장치 이름 고정 및 권한 고정](https://velog.io/@717lumos/Linux-USB-%EC%9E%A5%EC%B9%98-%EC%9D%B4%EB%A6%84-%EA%B3%A0%EC%A0%95%ED%95%98%EA%B8%B0-udev-%EC%84%A4%EC%A0%95-Symbolic-Link%EC%8B%AC%EB%B3%BC%EB%A6%AD-%EB%A7%81%ED%81%AC-%EB%A7%8C%EB%93%A4%EA%B8%B0)(Linux)
***
1/30   
🔹 [Kalman Filter(Esimating the velocity by poision)(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Kalman_Filter(Estimate%20the%20speed%20by%20position))   
🔹 [Kalman Filter 정리(Estimating the velocity by position)](https://velog.io/@soup1997/Linear-Kalman-FilterEstimating-the-speed-by-position)   
🔹 [Pytorch 기초](https://github.com/soup1997/Study-Alone/blob/origin/Pytorch/%ED%8C%8C%EC%9D%B4%ED%86%A0%EC%B9%98(PyTorch)%20%EA%B8%B0%EC%B4%88.ipynb) (50% 정리)   
🔹 고정 IP할당 및 와이파이 자동 설정(Linux)   
```bash
sudo cat /etc/wpa_supplicant/wpa_supplicant.conf

wpa_passphrase 와이파이이름 '비밀번호'

 -> 위 명령어 입력 시 아래 처럼 출력됨
network={
   ssid="와이파이이름"
   #psk="비밀번호"
   psk = ~~~
}
network={
   ssid="와이파이이름"
   #psk="비밀번호"
   psk=53d92a34f43d2dcda92866d8d99f70b895dd6bc247831a5310deea525d47eab1
}
 -> 위의 내용을 복사해서 wpa_supplicant.conf에 붙여넣기

sudo nano /etc/wpa_supplicant/wpa_supplicant.conf
sudo reboot
--------------------
# 고정 ip 할당

sudo nano /etc/dhcpcd.conf

interface wlan0
static ip_address=172.16.1.~
static routers=172.16.255.255
static netmask=255.255.0.0

sudo wpa_cli -i wlan0 reconfigure
```
***
1/31     
🔹 [Kalman Filter(Object Tracking)(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Kalman_Filter(Object%20Tracking))    
🔹 [Kalman Filter 정리(Object Tracking)](https://velog.io/@soup1997/Linear-Kalman-FilterObject-Tracking)   
🔹 [Pytorch 기초](https://github.com/soup1997/Study-Alone/blob/origin/Pytorch/%ED%8C%8C%EC%9D%B4%ED%86%A0%EC%B9%98(PyTorch)%20%EA%B8%B0%EC%B4%88.ipynb) (80% 정리)     
🔹 [밑바닥부터 시작하는 딥러닝(3장, 신경망)](https://github.com/soup1997/Study-Alone/tree/origin/Deep%20Learning/Neural%20Network)   
🔹 [Norm 이란?](https://bskyvision.com/entry/%EC%84%A0%ED%98%95%EB%8C%80%EC%88%98%ED%95%99-%EB%86%88norm%EC%9D%B4%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80)   
🔹 [Pytorch Gradient](https://gaussian37.github.io/dl-pytorch-gradient/)
***
2/1   
🔹 [Kalman Filter(Sensor Fusion(Accelerometer, Gyroscope)(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Kalman%20Filter(Sensor%20Fusion(Accelerometer%2C%20Gyroscope)))   
***
2/2   
🔹 [밑바닥부터 시작하는 딥러닝(4장, 신경망학습)](https://github.com/soup1997/Study-Alone/blob/origin/Deep%20Learning/%EC%8B%A0%EA%B2%BD%EB%A7%9D%20%ED%95%99%EC%8A%B5(4%EC%9E%A5)/%EB%B0%91%EB%B0%94%EB%8B%A5%EB%B6%80%ED%84%B0%20%EC%8B%9C%EC%9E%91%ED%95%98%EB%8A%94%20%EB%94%A5%EB%9F%AC%EB%8B%9D(4%EC%9E%A5).ipynb)   
🔹 [Pytorch 기초](https://github.com/soup1997/Study-Alone/blob/origin/Pytorch/%ED%8C%8C%EC%9D%B4%ED%86%A0%EC%B9%98(PyTorch)%20%EA%B8%B0%EC%B4%88.ipynb) (100% 정리)     
🔹 [Git 명령어 정리](https://hackmd.io/@oW_dDxdsRoSpl0M64Tfg2g/ByfwpNJ-K)
***
2/3    
🔹 [Kalman Filter 정리(Sensor Fusion(Accelerometer, Gyroscope)](https://velog.io/@soup1997/Linear-Kalman-FilterSensor-FusionAccelerometer-Gyroscope) (30% 정리)   
🔹 [밑바닥부터 시작하는 딥러닝(5장, 오차역전파)](https://github.com/soup1997/Study-Alone/blob/origin/Deep%20Learning/%EC%98%A4%EC%B0%A8%EC%97%AD%EC%A0%84%ED%8C%8C(5%EC%9E%A5)/%EB%B0%91%EB%B0%94%EB%8B%A5%EB%B6%80%ED%84%B0%20%EC%8B%9C%EC%9E%91%ED%95%98%EB%8A%94%20%EB%94%A5%EB%9F%AC%EB%8B%9D(5%EC%9E%A5).ipynb)   
🔹 [Why do we need to normalize dataset?](https://dongwooklee96.github.io/post/2021/11/06/%EB%8D%B0%EC%9D%B4%ED%84%B0-%EC%A0%95%EA%B7%9C%ED%99%94%EB%9E%80-%EB%A8%B8%EC%8B%A0%EB%9F%AC%EB%8B%9D.html)
***
2/6   
🔹 [Kalman Filter 정리(Sensor Fusion(Accelerometer, Gyroscope)](https://velog.io/@soup1997/Linear-Kalman-FilterSensor-FusionAccelerometer-Gyroscope) (100% 정리)   
🔹 [Extended Kalman Filter(Radar)(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Extended%20Kalman%20Filter(Radar))    
🔹 [Extended Kalman Filter 정리(Radar)](https://velog.io/@soup1997/Extended-Kalman-FilterRadar-Tracking)  
***
2/7   
🔹 [Extended Kalman Filter(Sensor Fusion(Accelerometer, Gyroscope))(MATLAB)](https://github.com/soup1997/Study-Alone/tree/origin/Matlab/Extended%20Kalman%20Filter(Sensor-fusion(Accelerometer%2C%20Gyroscope)))   
🔹 [밑바닥부터 시작하는 딥러닝(6장, 학습관련기술들)](https://github.com/soup1997/Study-Alone/blob/origin/Deep%20Learning/%ED%95%99%EC%8A%B5%EA%B8%B0%EC%88%A0(6%EC%9E%A5)/%EB%B0%91%EB%B0%94%EB%8B%A5%EB%B6%80%ED%84%B0%20%EC%8B%9C%EC%9E%91%ED%95%98%EB%8A%94%20%EB%94%A5%EB%9F%AC%EB%8B%9D(6%EC%9E%A5).ipynb)   
🔹 [Extended Kalman Filter 정리(Sensor Fusion(Accelerometer, Gyroscope))](https://velog.io/@soup1997/Extended-Kalman-FilterSensor-fusion-with-Gyroscope-and-Accelerometer)   
🔹 Difference between parameter and hyper parameter
```
Parameter is a value controlled through the train. 
But hyper parameter is modeled by setting the value by the user without training.
```   
🔹 The meaning of epoch, batch size, iteration   
![image](https://user-images.githubusercontent.com/86957779/217192018-60ee9108-6fc7-429b-a963-41281316d6f2.png)
```
* 한 번의 epoch는 인공 신경망에서 전체 데이터 셋에 대해 forward pass/backward pass 과정을 거친 것을 말함. 즉, 전체 데이터 셋에 대해 한 번 학습을 완료한 상태
* batch size는 한 번의 batch마다 주는 데이터 샘플의 size. 여기서 batch(보통 mini-batch라고 표현)는 나눠진 데이터 셋을 뜻함
* iteration는 epoch를 나누어서 실행하는 횟수라고 생각하면 됨.
``` 
***
2/8   
🔹 [Yaw angle calculation with EKF](https://github.com/soup1997/MPU9250-Sensor-Fusion) (테스트코드 수정 필요)   
🔹 [Pytorch 신경망 생성](https://github.com/soup1997/Study-Alone/blob/origin/Pytorch/%ED%8C%8C%EC%9D%B4%ED%86%A0%EC%B9%98%20%EC%8B%A0%EA%B2%BD%EB%A7%9D%20%EC%83%9D%EC%84%B1.ipynb)   
***
2/9
🔹 [Pytorch 신경망 생성(분류모델 추가)](https://github.com/soup1997/Study-Alone/blob/origin/Pytorch/%ED%8C%8C%EC%9D%B4%ED%86%A0%EC%B9%98%20%EC%8B%A0%EA%B2%BD%EB%A7%9D%20%EC%83%9D%EC%84%B1.ipynb)   
🔹 
