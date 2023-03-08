import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def load_data(data):
    csv_data = pd.read_csv(data)

    avg_temp = csv_data['avg']

    x_train, x_test = train_test_split(avg_temp, test_size=0.2)
    x_train = sliding_window(x_train)
    x_train, x_test = np.nan_to_num(np.array(
        x_train, dtype=np.float32)), np.nan_to_num(np.array(x_test, dtype=np.float32))

    return x_train, x_test


def sliding_window(x_train, WINDOW_SIZE=180):
    tmp = []
    for i in range(len(x_train) - WINDOW_SIZE):
        tmp.append(x_train[i:i+WINDOW_SIZE])

    return np.array(tmp)


def train_model(model, x_train, learning_rate=None, num_epochs=None):
    criterion = nn.MSELoss()
    optimizer = optim.Adam(model.parameters(), lr=learning_rate)
    torch.autograd.set_detect_anomaly(True)

    print(model)
    model.train()
    train_loss = 0
    for epoch in range(num_epochs+1):
        index = np.random.choice(x_train.shape[0], size=64, replace=False)
        x = torch.from_numpy(x_train[index])
        optimizer.zero_grad()
        output = model(x)
        loss = criterion(output, x)

        loss.backward()
        optimizer.step()

        train_loss.append(loss.item())
        if epoch % 10 == 0:
            print('Epoch: {0:4d}, Total train loss : {1:.4f}'.format(
                epoch, loss.item()))

    return model, train_loss


def plot_result(output, x_test):
    plt.plot(output.data.numpy().flatten(), label='prediction')
    plt.plot(x_test.flatten(), label='Original')
    plt.xlabel('Temperature(ºC)')
    plt.ylabel('Date')
    plt.grid(True)
    plt.show()


def eval_model(model, x_test):
    x_test = torch.from_numpy(x_test)
    model.eval()

    with torch.no_grad():
        output = model(x_test)
        plot_result(output, x_test)


class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()

        self.fc1 = nn.Linear(180, 128)
        self.fc2 = nn.Linear(128, 64)

        self.fc3 = nn.Linear(64, 128)
        self.fc4 = nn.Linear(128, 180)

    def forward(self, x):
        # Encoder
        x = F.relu(self.fc1(x))
        x = self.fc2(x)

        # Decoder
        x = F.relu(self.fc3(x))
        x = self.fc4(x)

        return x


if __name__ == '__main__':
    x_train, x_test = load_data('./ta_20230303181535.csv')
    model = AutoEncoder()
    model = train_model(model, x_train, learning_rate=0.001, num_epochs=1000)
    #eval_model(model, x_test)