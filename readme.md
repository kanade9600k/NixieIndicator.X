# ニキシー管表示器

## 使い方

I2C通信で表示する値を受け取ります。

| 何ビット目か | 内容                                    | 
| ------------ | --------------------------------------- | 
| 0            | 0桁目(最上位桁)のドット(数字の左につく) | 
| 1            | 0桁目の数字・記号                       | 
| 2            | 1桁目のドット                           | 
| 3            | 1桁目の数字・記号                       | 
| 4            | 2桁目のドット                           | 
| 5            | 2桁目の数字・記号                       | 
| 6            | 3桁目のドット                           | 
| 7            | 3桁目の数字・記号                       | 
| 8            | 4桁目のドット                           | 
| 9            | 4桁目の数字・記号                       | 
| 10           | 5桁目のドット                           | 
| 11           | 5桁目の数字・記号                       | 
| 12           | 6桁目のドット                           | 
| 13           | 6桁目の数字・記号                       | 
| 14           | 7桁目のドット                           | 
| 15           | 7桁目の数字・記号                       | 
| 16           | 8桁目のドット                           | 
| 17           | 8桁目の数字・記号                       | 
| 18           | 9桁目のドット                           | 
| 19           | 9桁目の数字・記号                       | 