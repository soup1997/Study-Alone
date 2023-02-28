# `LSTMCell`

## Equation
<div align='center'>

![image](https://user-images.githubusercontent.com/86957779/221812080-767a04d2-b48b-4967-aa49-29dac00a347f.png)

</div>

## Parameters
`input_size`: 입력으로 주어지는 데이터의 feature의 갯수   

`hidden_size`: hidden state $h$의 벡터 크기   

`num_layers`: 재귀 층의 갯수   

<div align='center'>

![image](https://user-images.githubusercontent.com/86957779/221811500-0bf453dc-925f-4d36-969c-50847de33091.png)

</div>

`bias`: 위의 수식에서 b에 해당하는 편향(bias)값, default는 True

`batch_first`: batch size를 맨 앞으로 설정할 것인가를 다루는 변수, True일 경우 모델의 입력 데이터는 (batch, seq, feature)의 형태를 가지게 된다.

`dropout`: 모델의 과적합 방지, torch의 test 단계에서 model.eval() 호출 시 dropout은 자동해제   
