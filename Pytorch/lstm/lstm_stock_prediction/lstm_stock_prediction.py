import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import TensorDataset
from torch.utils.data import DataLoader

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler

import warnings
warnings.filterwarnings("ignore")

# 데이터셋 생성 함수
def build_dataset(time_series, seq_length):
    dataX = []
    dataY = []
    for i in range(0, len(time_series)-seq_length):
        _x = time_series[i:i+seq_length, :]
        _y = time_series[i+seq_length, [-1]]
        dataX.append(_x)
        dataY.append(_y)

    return np.array(dataX), np.array(dataY)


def MAE(true, pred):
    return np.mean(np.abs(true-pred))


def train_model(model, train_df, epochs=None, lr=None, device=None):
    criterion = nn.MSELoss().to(device)
    optimizer = optim.Adam(model.parameters(), lr=lr)
    
    train_hist = np.zeros(epochs)

    for epoch in range(epochs):
        avg_loss = 0
        total_batch = len(train_df)

        for batch_idx, (trainX, trainY) in enumerate(train_df):
            model.reset_hidden_state(trainX)

            # H(x) 계산
            outputs = model(trainX)

            loss = criterion(outputs, trainY)

            # loss로 H(x) 개선
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            avg_loss += loss/total_batch

        train_hist[epoch] = avg_loss

        if epoch % 10 == 0:
            print('Epoch: {:04d}, train loss : {:.4f}'.format(epoch, avg_loss))

    return model, train_hist


class Net(nn.Module):
    def __init__(self, input_dim, hidden_dim, seq_len, output_dim, layers):
        super(Net, self).__init__()
        self.hidden_dim = hidden_dim
        self.seq_len = seq_len
        self.output_dim = output_dim
        self.layers = layers

        self.lstm = nn.LSTM(input_size=input_dim, 
                            hidden_size=hidden_dim, 
                            num_layers=layers,
                            batch_first=True)
        
        self.fc = nn.Linear(in_features=hidden_dim, 
                            out_features=output_dim, 
                            bias=True)

    def reset_hidden_state(self, x):
        h_0 = torch.zeros(self.layers, x.size(0), self.hidden_dim)
        c_0 = torch.zeros(self.layers, x.size(0), self.hidden_dim)

        return h_0, c_0

    def forward(self, x):
        h_0, c_0 = self.reset_hidden_state(x)
        output, (h_t, c_t) = self.lstm(x, (h_0, c_0))
        x = self.fc(output[:, -1])
        return x


if __name__ == '__main__':
    '''
    Data Column(Input Demension)
    |Open|High|Low|Volume|Close|
    '''
    df = pd.read_csv('C:\\Users\\soup1997\\Desktop\\soup1997\\Study-Alone\\Pytorch\\lstm\\lstm_stock_prediction\\data-02-stock_daily.csv')

    # 7일간의 데이터가 입력으로 들어가고 batch size는 임의로 지정
    seq_length = 7
    batch = 100

    # 데이터를 역순으로 정렬하여 전체 데이터의 70% 학습, 30% 테스트에 사용
    # Total Dataset: 733
    # Train Dataset: 513
    # Test Dataset: 220

    df = df[::-1]
    train_size = int(len(df)*0.7)
    train_set = df[0:train_size]
    test_set = df[train_size-seq_length:]

    # Dataset Normalization
    scaler_x, scaler_y = MinMaxScaler(), MinMaxScaler()

    scaler_x.fit(train_set.iloc[:, :-1])

    train_set.iloc[:, :-1] = scaler_x.transform(train_set.iloc[:, :-1])
    test_set.iloc[:, :-1] = scaler_x.transform(test_set.iloc[:, :-1])

    scaler_y.fit(train_set.iloc[:, [-1]])

    train_set.iloc[:, -1] = scaler_y.transform(train_set.iloc[:, [-1]])
    test_set.iloc[:, -1] = scaler_y.transform(test_set.iloc[:, [-1]])

    trainX, trainY = build_dataset(np.array(train_set), seq_length)
    testX, testY = build_dataset(np.array(test_set), seq_length)

    trainX_tensor, trainY_tensor = torch.FloatTensor(trainX), torch.FloatTensor(trainY)

    testX_tensor, testY_tensor = torch.FloatTensor(testX), torch.FloatTensor(testY)

    dataset = TensorDataset(trainX_tensor, trainY_tensor)

    dataloader = DataLoader(dataset, batch_size=batch, shuffle=True, drop_last=True)

    #================================================================
    
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    net = Net(input_dim=5, hidden_dim=10, seq_len=seq_length, output_dim=1, layers=1).to(device)
    print(net)

    model, train_hist = train_model(net, dataloader, epochs=1000, lr=0.001, device=device)

    with torch.no_grad():
        pred = []
        for pr in range(len(testX_tensor)):
            predicted = model(torch.unsqueeze(testX_tensor[pr], 0))
            predicted = torch.flatten(predicted).item()
            pred.append(predicted)

        pred_inverse = scaler_y.inverse_transform(np.array(pred).reshape(-1, 1))
        testY_inverse = scaler_y.inverse_transform(testY_tensor)
    
    #================================================================

    print('MAE SCORE : ', MAE(pred_inverse, testY_inverse))
          
    plt.figure(0, figsize=(10, 4))
    plt.plot(train_hist, label="Training loss")
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.savefig('train_loss.png')

    plt.figure(1, figsize=(10, 4))
    plt.plot(np.arange(len(pred_inverse)), pred_inverse, label='pred')
    plt.plot(np.arange(len(testY_inverse)), testY_inverse, label='true')
    plt.xlabel('Day')
    plt.ylabel('Stock Price')
    plt.legend()
    plt.savefig('stock price prediction.png')
    plt.show()