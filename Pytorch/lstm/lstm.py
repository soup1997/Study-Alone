'''
구글 주식 데이터로 1주전(1일 ~ 7일) 데이터를 토대로 8일째 가격을 예측하는 모델

이전 7일의 정보를 활용하여 그 다음 종가를 예측하므로 Sequence = 7, Output dimension = 1이다. 
'''

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data import DataLoader
from torch.utils.data import TensorDataset

import numpy as np
import pandas as pd
import random
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler

# Dataset을 정의하고, Dataloader에 전달(미니배치학습, 데이터 셔플, 병렬처리를 수행할 수 있음)
def build_dataset(time_series, seq_length):
    dataX = []
    dataY = []
    for i in range(0, len(time_series)-seq_length):
        _x = time_series[i:i+seq_length, :]
        _y = time_series[i+seq_length, [-1]]
        dataX.append(_x)
        dataY.append(_y)

    return np.array(dataX), np.array(dataY)


def train_model(model, train_df, num_epochs=None, lr=None, verbose=10, patience=10):
    global device

    criterion = nn.MSELoss().to(device)
    optimizer = optim.Adam(model.parameters(), lr)
    nb_epochs = num_epochs

    # epoch 마다 loss 저장
    train_hist = np.zeros(nb_epochs)

    for epoch in range(nb_epochs):
        avg_cost = 0
        total_batch = len(train_df)

        for batch_idx, samples in enumerate(train_df):
            x_train, y_train = samples

            # seq별 hidden state reset
            model.reset_hidden_state()

            # H(x) 계산
            outputs = model(x_train)

            # Cost 계산
            loss = criterion(outputs, y_train)

            # Cost로 H(x) 업데이트
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            avg_cost += loss / total_batch

        train_hist[epoch] = avg_cost

        if epoch % verbose == 0:
            print('Epoch: {:04d}, train loss: {:.4f}'.format(epoch, avg_cost))

        # Patience 번째 마다 early stopping 여부 확인
        if (epoch % patience == 0) & (epoch != 0):

            # loss가 증가하였다면
            if train_hist[epoch-patience] < train_hist[epoch]:
                print("Early Stopping")
                break

    return model.eval(), train_hist

# 평가 척도
def MAE(true, pred):
    res = np.mean(np.abs(true-pred))
    print('MAE SCORE: {}'.format(res))
    return res


class Net(nn.Module):
    def __init__(self, input_dim, hidden_dim, seq_len, output_dim, layers):
        super(Net, self).__init__()
        self.hidden_dim = hidden_dim
        self.seq_len = seq_len
        self.output_dim = output_dim
        self.layers = layers

        self.lstm = nn.LSTM(input_dim, hidden_dim,
                            num_layers=layers, batch_first=True)
        self.fc = nn.Linear(hidden_dim, output_dim, bias=True)

    # seq별로 hidden state를 초기화 하는 함수로 이전 seq의 영향을 받지 않게 하기 위함
    def reset_hidden_state(self):
        self.hidden = (torch.zeros(self.layers, self.seq_len, self.hidden_dim),
                       torch.zeros(self.layers, self.seq_len, self.hidden_dim))

    def forward(self, x):
        x = self.lstm(x)
        x = self.fc(x[:, -1])
        return x


device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

df = pd.read_csv(
    'C:/Users/soup1997/Desktop/lstm/data-02-stock_daily.csv')  # 데이터 불러오기

seq_length = 7  # 7일간의 입력 데이터
batch = 100

# 데이터를 역순으로 정렬하여 전체 데이터의 70% 학습, 30% 테스트에 사용
df = df[::-1]
train_size = int(len(df) * 0.7)  # train data
train_set = df[0:train_size]
test_set = df[train_size-seq_length:]

'''
파이토치에서는 데이터를 좀 더 쉽게 다룰 수 있도록 유용한 도구로서 
데이터셋(Dataset)과 데이터로더(DataLoader)를 제공하는데 
이를 사용하면 미니 배치 학습, 데이터 셔플, 병렬 처리 등 간단히 수행할 수 있다. 
기본적인 사용 방법은 Dataset을 정의하고 이를 DataLoader에 전달하는 것이다.  
'''
# Input scale
scaler_x = MinMaxScaler()
scaler_x.fit(train_set.iloc[:, :-1])

train_set.iloc[:, :-1] = scaler_x.transform(train_set.iloc[:, :-1])
test_set.iloc[:, :-1] = scaler_x.transform(test_set.iloc[:, :-1])

# Output scale
scaler_y = MinMaxScaler()
scaler_y.fit(train_set.iloc[:, [-1]])

train_set.iloc[:, -1] = scaler_y.transform(train_set.iloc[:, [-1]])
test_set.iloc[:, -1] = scaler_y.transform(test_set.iloc[:, [-1]])

trainX, trainY = build_dataset(np.array(train_set), seq_length)
testX, testY = build_dataset(np.array(test_set), seq_length)

trainX_tensor = torch.FloatTensor(trainX)
trainY_tensor = torch.FloatTensor(trainY)

testX_tensor = torch.FloatTensor(testX)
testY_tensor = torch.FloatTensor(testY)

dataset = TensorDataset(trainX_tensor, trainY_tensor)

dataloader = DataLoader(dataset,
                        batch_size=batch,
                        shuffle=True,
                        drop_last=True)

'''
입력 컬럼은 5개, 
output 형태는 1개이며 hidden_state는 10개, 학습률은 0.01 등 임의 지정하였다.
'''
data_dim = 5
hidden_dim = 10
output_dim = 1
learning_rate = 0.01
nb_epochs = 100


# 모델 학습
net = Net(data_dim, hidden_dim, seq_length, output_dim, 1).to(device)

model, train_hist = train_model(
    net, dataloader, num_epochs=nb_epochs, lr=learning_rate, verbose=20, patience=10)

# 모델 평가
with torch.no_grad():
    pred = []

    for pr in range(len(testX_tensor)):
        model.reset_hidden_state()

        predicted = model(torch.unsqueeze(testX_tensor[pr], 0))
        predicted = torch.flatten(predicted).item()
        pred.append(predicted)

    pred_inverse = scaler_y.inverse_transform(np.array(pred).reshape(-1, 1))
    testY_inverse = scaler_y.inverse_transform(np.array(testY_tensor))

    score = MAE(pred_inverse, testY_inverse)

plt.figure(1)
plt.figure(figsize=(10, 4))
plt.plot(train_hist, label='Training Loss')
plt.xlabel('epoch')
plt.ylabel('loss')
plt.legend()

plt.figure(2)
plt.figure(figsize=(8, 3))
plt.plot(np.arange(len(pred_inverse)), pred_inverse, label='pred')
plt.plot(np.arange(len(testY_inverse)), testY_inverse, label='true')
plt.title("Loss plot")
plt.show()