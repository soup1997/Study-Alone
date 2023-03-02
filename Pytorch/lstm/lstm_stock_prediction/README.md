`LSTM`
```python
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
```
# Usage
`torch.nn.LSTM(input_size, hidden_size, num_layers, bias=True, batch_first=True, dropout, bidirectional)`
* `input_size`:input의 feature dimension을 넣어주어야 한다. time step이 아닌 input feature dimension
* `hidden_size`: 내부에서 어떤 feature dimension으로 바꿔주고 싶은지를 나타냄
* `num_layers`: 재귀 층의 갯수

<div align='center'>

![image](https://user-images.githubusercontent.com/86957779/221811500-0bf453dc-925f-4d36-969c-50847de33091.png)

</div>

* `bias`: bias term을 둘 것인가 (Default: True)
* `batch_first`: batch_first=True라면, (Batch_size, Time_step, Input_feature_dimension) 순서 (Default: False)
* `dropout`: Dropout의 비율, generalization 잘 안되면 조정
* `bidirectional`: 양방향 여부 (bidirectional 하면 [forward, backword]가 되어 feature dimension 2배)

# Reset State
```python
output, (h_t, c_t) = self.lstm(x, (h_0, c_0))
```
```bash
Input은 입력 sequence와 초기 state (LSTM이면 {hidden state, cell state} 그 외는 {hidden state})로 구성
초기 state가 없다면 넣어주지 않아도 되고 자동으로 zero로 설정 
입력 sequence의 dimension은 (Batch, Time_step, Feature dimension) 순 (batch_first=True 기준)
```
