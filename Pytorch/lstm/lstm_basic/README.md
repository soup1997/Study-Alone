# LSTM Basic

```python
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
```
LSTM(   
  (lstm1): LSTMCell(1, 51)   
  (lstm2): LSTMCell(51, 51)   
  (linear): Linear(in_features=51, out_features=1, bias=True)   
)   

* train input.shape: torch.Size([1, 999]), train target.shape: torch.Size([1, 999])   
* test input.shape: torch.Size([1, 999]), test target.shape: torch.Size([1, 999])    
