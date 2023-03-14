'''
1. x를 예측하고, 신경망에 의미 있는 정보가 쌓이도록 설계된 신경망이 바로 오토인코더입니다. 
즉 오토인코더에서는 입력도 x, 정답도 x 입니다.

2. 오찻값에도 x를 얼마나 복원했는지를 뜻하는 복원오차, 혹은 정보손실값(reconstruction loss)이라는 용어를 사용합니다.

3. 오토인코더는 입력과 출력의 크기는 같지만 중간으로 갈수록 신경망의 차원이 줄어든다는 것입니다.

4. 작은 차원으로 압축된 표현을 잠재변수(latent variable)라 하고, 간단히 z라고도 합니다.

5. 잠재 변수의 앞뒤를 구분하여 앞부분을 인코더(encoder), 뒷부분을 디코더(decoder)라고 합니다.인코더는 정보를 받아 압축하고, 디코더는 압축된 표현을 풀어 입력을 복원하는 역할을 합니다.

6. 오토인코더에서는 필연적으로 정보의 손실이 일어나지만 이는 중요한 정보만 남겨두는 일종의 데이터 가공이라고 볼 수 있습니다. 이런 특징으로 인해 오토인코더는 주로 복잡한 비선형 데이터의 차원을 줄이는 용도로 쓰입니다.
'''

import torch
import torchvision
import torch.nn.functional as F
from torch import nn, optim
from torchvision import transforms, datasets

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import numpy as np


def load_data():
    BATCH_SIZE = 64

    trainset = datasets.FashionMNIST(
        root='./.data/', 
        train=True, 
        download=True, 
        transform=transforms.ToTensor()
    )

    train_loader = torch.utils.data.DataLoader(
        dataset = trainset,
        batch_size = BATCH_SIZE,
        shuffle = True
    )

    return trainset, train_loader

def image_check(trainset):
    view_data = trainset.data[:5].view(-1, 28*28)

    view_data = view_data.type(torch.FloatTensor) / 255.

    return view_data

def train(autoencoder, train_loader):
    global DEVICE
    train_loss = 0
    autoencoder.train()

    for batch_idx, (x, label) in enumerate(train_loader):
        x = x.view(-1, 28*28).to(DEVICE)
        y = x.view(-1, 28*28).to(DEVICE)
        label = label.to(DEVICE)

        encoded, decoded = autoencoder(x)

        loss = criterion(decoded, y) # decoded와 원본이미지(y) 사이의 평균제곱오차를 구한다.
        optimizer.zero_grad() # 기울기에 대한 정보를 초기화 한다.
        loss.backward() # 기울기를 구한다.
        optimizer.step() # 최적화 진행
        train_loss += loss.item()

    return train_loss


class Autoencoder(nn.Module):
    def __init__(self):
        super(Autoencoder, self).__init__()

        self.encoder = nn.Sequential(
            nn.Linear(28*28 , 128),
            nn.ReLU(),
            nn.Linear(128, 64),
            nn.ReLU(),
            nn.Linear(64, 12),
            nn.ReLU(),
            nn.Linear(12, 3) # 입력의 특징을 3차원으로 압축 (출력값이 잠재변수)
        )

        self.decoder = nn.Sequential(
            nn.Linear(3, 12),
            nn.ReLU(),
            nn.Linear(12, 64),
            nn.ReLU(),
            nn.Linear(64, 128),
            nn.ReLU(),
            nn.Linear(128, 28*28),
            nn.Sigmoid() # 픽셀 값을 0 ~ 1로 mapping
        )
    
    def forward(self, x):
        encoded = self.encoder(x) # encoded라는 잠재변수를 만듦.
        decoded = self.decoder(encoded) # decoder를 통해 decoded라는 복원이미지를 생성
        return encoded, decoded
    
if __name__ =='__main__':
    # Hyper Parameter
    EPOCH = 10
    DEVICE = torch.device("cuda:0" if torch.cuda.is_available() else 'cpu')
    
    autoencoder = Autoencoder().to(device=DEVICE)
    optimizer = optim.Adam(autoencoder.parameters(), lr=0.005)
    criterion = nn.MSELoss()

    trainset, train_loader = load_data()
    view_data = image_check(trainset=trainset)

    for epoch in range(1, EPOCH+1):
        loss = train(autoencoder=autoencoder, train_loader=train_loader)

        # 디코더에서 나온 이미지를 시각화 하기
        test_x = view_data.to(DEVICE)
        _, decoded_data = autoencoder(test_x)

        f, a = plt.subplots(2, 5, figsize=(5, 2))
        print("Epoch : {}, Loss: {}".format(epoch, loss), end="\n")


        # 원본과 디코딩 결과 비교하기
        for i in range(5):
            img = np.reshape(view_data.data.numpy()[i], (28, 28))
            a[0][i].imshow(img, cmap='gray')
            a[0][i].set_xticks(())
            a[0][i].set_yticks(())

        for i in range(5):
            img = np.reshape(decoded_data.to('cpu').data.numpy()[i], (28, 28))
            a[1][i].imshow(img, cmap='gray')
            a[1][i].set_xticks(())
            a[1][i].set_yticks(())

    '''
    Epoch : 1, Loss: 33.0600119587034
    Epoch : 2, Loss: 23.555675331503153
    Epoch : 3, Loss: 22.399405159056187
    Epoch : 4, Loss: 21.915830571204424
    Epoch : 5, Loss: 21.54024081490934
    Epoch : 6, Loss: 21.218671457841992
    Epoch : 7, Loss: 21.165826940909028
    Epoch : 8, Loss: 21.033127158880234
    Epoch : 9, Loss: 21.008933499455452
    Epoch : 10, Loss: 20.936807598918676
    '''

    # 잠재변수 들여다 보기
    # 잠재변수를 3D 플롯으로 시각화
    view_data = trainset.data[:200].view(-1, 28*28) #원본이미지 200개를 준비합니다
    view_data = view_data.type(torch.FloatTensor)/255.
    test_x = view_data.to(DEVICE)
    encoded_data, _ = autoencoder(test_x)
    encoded_data = encoded_data.to("cpu")

    CLASSES = {
    0: 'T-shirt/top',
    1: 'Trouser',
    2: 'Pullover',
    3: 'Dress',
    4: 'Coat',
    5: 'Sandal',
    6: 'Shirt',
    7: 'Sneaker',
    8: 'Bag',
    9: 'Ankle boot'}

    fig = plt.figure(figsize=(10,8))
    ax = Axes3D(fig)

    X = encoded_data.data[:, 0].numpy()
    Y = encoded_data.data[:, 1].numpy()
    Z = encoded_data.data[:, 2].numpy() #잠재변수의 각 차원을 numpy행렬로 변환합니다.

    labels = trainset.targets[:200].numpy() #레이블도 넘파이행렬로 변환합니다.

    for x, y, z, s in zip(X, Y, Z, labels): #zip()은 같은 길이의 행렬들을 모아 순서대로 묶어줍니다.
        name = CLASSES[s]
        color = cm.rainbow(int(255*s/9))
        ax.text(x, y, z, name, backgroundcolor=color)

    ax.set_xlim(X.min(), X.max())
    ax.set_ylim(Y.min(), Y.max())
    ax.set_zlim(Z.min(), Z.max())
    plt.show()