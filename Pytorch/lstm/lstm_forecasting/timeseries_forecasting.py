import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def create_dataset(dataset, sequence=3):
    '''
    Transform a time series into a prediction dataset

    Args:
        dataset: A numpy array of time series, first dimension is the time steps
        sequence: Size of window for prediction
    '''

    X, y = [], []
    for i in range(len(dataset)-sequence):
        feature = dataset[i:i+sequence]
        target = dataset[i+1:i+sequence+1]
        X.append(feature)
        y.append(target)

    X, y = torch.Tensor(X), torch.Tensor(y)

    # Shape: (Window sample, time steps, features)
    print("X shape: {}, y shape: {}".format(X.shape, y.shape))
    
    return X, y

def train(model, train_loader, X_train, y_train):
    EPOCHS = 5000
    model.train()
    
    for epoch in range(1, EPOCHS+1):
        train_loss = 0
        total_batch = len(X_train)

        for batch_idx, (X_batch, y_batch) in enumerate(train_loader):
            y_pred = model(X_batch)
            loss = criterion(y_pred, y_batch)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            train_loss += loss.item() / total_batch

        if epoch % 100 == 0:
            print("Epoch: {0:04d}: Train loss {1:.4f}".format(epoch, train_loss), end=",")

            with torch.no_grad():
                y_pred = model(X_train) 
                train_rmse = np.sqrt(criterion(y_pred, y_train))

                y_pred = model(X_test)
                test_rmse = np.sqrt(criterion(y_pred, y_test))
            
            print('Train RMSE: {0:.4f}, Test RMSE: {1:.4f}'.format(train_rmse, test_rmse))
    
    return model


def eval(model, timeseries, X_train, X_test, sequence=3):
    model.eval()

    with torch.no_grad():
        train_plot = np.ones_like(timeseries) * np.nan
        train_plot[sequence:train_size] = model(X_train)[:, -1, :]

        test_plot = np.ones_like(timeseries) * np.nan
        test_plot[train_size+sequence:len(timeseries)] = model(X_test)[:, -1, :]
    
    plt.plot(timeseries, label='Ground Truth')
    plt.plot(train_plot, c='r', label='train set')
    plt.plot(test_plot, c='g', label='test set')
    plt.legend()
    plt.show()

class LSTM(nn.Module):
    def __init__(self, input_size, hidden_size, num_layers):
        super(LSTM, self).__init__()

        self.input_size = input_size
        self.hidden_size = hidden_size
        self.num_layers = num_layers

        self.lstm = nn.LSTM(input_size=input_size, 
                            hidden_size=hidden_size, 
                            num_layers=num_layers, 
                            bias=True,
                            batch_first=True
                            )
        
        self.linear = nn.Linear(50, 1)
        

    def forward(self, x):
        x, (h_t, c_t) = self.lstm(x)
        x = self.linear(x)

        return x


if __name__=='__main__':
    df = pd.read_csv('./lstm_forecasting/airline-passengers.csv')
    timeseries = df[["Passengers"]].values.astype('float32')

    train_size = int(len(timeseries) * 0.67)
    trainset, testset = timeseries[:train_size], timeseries[train_size:]

    X_train, y_train = create_dataset(trainset, sequence=3)
    X_test, y_test = create_dataset(testset, sequence=3)

    train_loader = DataLoader(TensorDataset(X_train, y_train),
                              shuffle=True,
                              batch_size=8)
    
    model = LSTM(input_size=1, hidden_size=50, num_layers=2)
    optimizer = optim.Adam(model.parameters(), lr=1e-3)
    criterion = nn.MSELoss()

    train(model, train_loader, X_train, y_train)
    eval(model, timeseries, X_train, X_test)

    PATH = './'
    torch.save(model.state_dict(), PATH + 'model_state_dict.pt')