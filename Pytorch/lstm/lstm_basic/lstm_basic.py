import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset
import matplotlib.pyplot as plt

N = 100
L = 1000
T = 20

x = np.empty((N, L), dtype=np.float32)
x[:] = np.array(range(L)) + np.random.randint(-4*T, 4*T, N).reshape(N, 1)
y = np.sin(x/1.0/T).astype(np.float32)

plt.figure(figsize=(10, 8))
plt.title('Sine Wave')
plt.xlabel('x')
plt.ylabel('y')
plt.xticks(fontsize=20)
plt.yticks(fontsize=20)
plt.plot(np.arange(x.shape[1]), y[0, :], 'r', linewidth=2.0)
#plt.show()


class LSTM(nn.Module):
    def __init__(self, n_hidden=51):
        super(LSTM, self).__init__()
        self.n_hidden = n_hidden

        # lstm1, lstm2, linear
        self.lstm1 = nn.LSTMCell(input_size=1, hidden_size=self.n_hidden)
        self.lstm2 = nn.LSTMCell(
            input_size=self.n_hidden, hidden_size=self.n_hidden)
        self.linear = nn.Linear(in_features=self.n_hidden, out_features=1)

    def forward(self, x, future=0):
        outputs = []
        n_samples = x.size(0)

        h_t = torch.zeros(n_samples, self.n_hidden, dtype=torch.float32)
        c_t = torch.zeros(n_samples, self.n_hidden, dtype=torch.float32)
        h_t2 = torch.zeros(n_samples, self.n_hidden, dtype=torch.float32)
        c_t2 = torch.zeros(n_samples, self.n_hidden, dtype=torch.float32)

        for input_t in x.split(1, dim=1):
            # N, 1
            h_t, c_t = self.lstm1(input_t, (h_t, c_t))
            h_t2, c_t2 = self.lstm2(h_t, (h_t2, c_t2))
            output = self.linear(h_t2)
            outputs.append(output)

        for _ in range(future):
            h_t, c_t = self.lstm1(output, (h_t, c_t))
            h_t2, c_t2 = self.lstm2(h_t, (h_t2, c_t2))
            output = self.linear(h_t2)
            outputs.append(output)

        outputs = torch.cat(outputs, dim=1)
        return outputs


if __name__ == '__main__':
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

    '''
    DataLoader 는 사용하고자 하는 모델을 초기화 하고 훈련 루프가 시작되기 전에 위치하는 것이 일반적이다. 
    데이터 정규화를 위한 mean 과 std 값, 그리고 batch_size, shuffle 과 같은 옵션은 
    상황에 맞게 configuration 하면 되겠다.
    '''
    # y = 100, 1000
    train_input = torch.from_numpy(y[3:, :-1])  # 97, 999
    train_target = torch.from_numpy(y[3:, 1:])  # 97, 999
    train_loader = DataLoader(TensorDataset(train_input, train_target),
                              batch_size=1,
                              shuffle=True)

    test_input = torch.from_numpy(y[:3, :-1])  # 3, 999
    test_target = torch.from_numpy(y[:3, 1:])  # 3, 999
    test_loader = DataLoader(TensorDataset(test_input, test_target),
                             batch_size=3,
                             shuffle=True)

    model = LSTM().to(device)
    criterion = nn.MSELoss().to(device)

    optimizer = optim.LBFGS(model.parameters(), lr=0.05)  # Limited-memory BFGS

    epochs = 13

    train_input, train_target = next(iter(train_loader))
    print("train input.shape: {}, train target.shape: {}".format(
        train_input.shape, train_target.shape))

    test_input, test_target = next(iter(test_loader))
    print("test input.shape: {}, test target.shape: {}".format(
        train_input.shape, train_target.shape))

    for epoch in range(epochs):
        print('Epoch: {}'.format(epoch))
        
        for train_input, train_target in train_loader:
            train_input, train_target = train_input.to(
                device), train_target.to(device)

            def closure():
                optimizer.zero_grad()
                out = model(train_input)
                loss = criterion(out, train_target)
                print('Train loss: {}'.format(loss.item()))
                loss.backward()
                return loss   
        optimizer.step(closure)

        with torch.no_grad():  # Gradient 추적 X
            for test_input, test_target in test_loader:
                test_input, test_target = test_input.to(
                    device), test_target.to(device)

                future = 1000
                pred = model(test_input, future=future)
                loss = criterion(pred[:, :-future], test_target)
                print("Test loss: {}".format(loss.item()))
                y = pred.detach().numpy()

        plt.figure(figsize=(12, 6))
        plt.title('Epoch: {}'.format(epoch+1))
        plt.xlabel('x')
        plt.ylabel('y')
        plt.xticks(fontsize=20)
        plt.yticks(fontsize=20)

        n = train_input.shape[1]  # 999

        plt.plot(np.arange(n), y[0][:n], 'r', linewidth=2.0)
        plt.plot(np.arange(n, n+future), y[0][n:], 'r:', linewidth=2.0)

        plt.plot(np.arange(n), y[1][:n], 'b', linewidth=2.0)
        plt.plot(np.arange(n, n+future), y[1][n:], 'b:', linewidth=2.0)

        plt.plot(np.arange(n), y[2][:n], 'g', linewidth=2.0)
        plt.plot(np.arange(n, n+future), y[2][n:], 'g:', linewidth=2.0)

        plt.savefig("Prediction %d.png" % epoch)
        plt.close()