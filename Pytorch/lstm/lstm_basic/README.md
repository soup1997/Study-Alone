# `LSTM Cell`
```python
def LSTMCell(input, hidden, w_ih, w_hh, b_ih=None, b_hh=None):
    if input.is_cuda:
        ...
    hx, cx = hidden
    gates = F.linear(input, w_ih, b_ih) + F.linear(hx, w_hh, b_hh)
    ingate, forgetgate, cellgate, outgate = gates.chunk(4, 1)
    ingate     = F.sigmoid(ingate)
    forgetgate = F.sigmoid(forgetgate)
    cellgate   = F.tanh(cellgate)
    outgate    = F.sigmoid(outgate)
    cy = (forgetgate * cx) + (ingate * cellgate)
    hy = outgate * F.tanh(cy)
    return hy, cy
```
<div align='center'>
  
![1_hl9UVtgIcQkDIGD8VFykdw](https://user-images.githubusercontent.com/86957779/221815686-7781cc4a-bc7b-4aa3-8255-63d9705d1499.png)
  
</div>

## Equation
$i_t=\sigma(W_{ii}x_t+b_{ii}+W_{hi}h_{t-1}+b_{hi})$   
$f_t=\sigma(W_{if}x_t+b_{if}+W_{hf}h_{t-1}+b_{hf}$   
$g_t=\tanh(W_{ig}x_t+b_{ig}+W_{hg}h_{t-1}+b_{hg})$   
$o_t=\sigma(W_{io}x_t+b_{io}+W_{ho}h_{t-1}+b_{ho})$   
$c_t=f_t\odot c_{t-1}+i_t\odot g_t$   
$h_t=o_t\odot\tanh(c_t)$


## Parameters
`torch.nn.LSTMCell(input_size, hidden_size, bias=True, device=None, dtype=None)`   
* `input_size`: 입력으로 주어지는 데이터의 feature의 갯수   

* `hidden_size`: hidden state $h$의 벡터 크기   
