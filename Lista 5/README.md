# aiRango

## Descrição do Problema 

Uma rede de Fast Food decidiu implementar um sistema de delivery por aplicativo. O funcionamento básico do sistema consiste em que os pedidos sejam encaminhados à central e colocados numa fila por ordem de chegada. Cada um dos M entregadores cadastrados pode aceitar um pedido para entrega. Nesse instante, o sistema calculará a melhor rota a ser seguida. A rota consiste em encaminhar o entregador da sua posição atual X até um dos restaurantes da rede na posição Y, no qual ele fará a coleta do pedido, e em seguida até o endereço de entrega Z. A rota escolhida deverá ser a de menor comprimento total X->Y->Z. Um pedido pode também ser cancelado, desde que ainda não tenha sido aceite para entrega.

### Input Specification

O mapa da cidade será codificado por um grafo, em que cada ponto de coleta/entrega corresponde a um vértice. Uma aresta (A, B, L) corresponde a uma via de mão-dupla e comprimento L entre os pontos A e B. Sendo assim, a entrada começa com uma linha

> V E N M
<p> onde

* V corresponde ao número de localidades (numeradas 0..V-1)
* E corresponde ao número de vias interligando essas localidades
* N corresponde à quantidade de lojas da rede (numeradas 0..N-1)
* M corresponde ao número de entregadores (numerados 0..M-1)
* Em seguida temos E linhas, cada uma com três inteiros no formato

>A B L
<p> representando uma via entre A e B com comprimento L, como explicado acima.

Logo após temos uma linha com N números distintos

> Y[0] Y[1] ... Y[N-1]
correspondentes às localidades dos N restaurantes da rede.

Supõe-se que, inicialmente, todos os entregadores estejam estacionados em Y[0].

A partir de então temos várias linhas numa das formas a seguir:

* ```NEW I Z``` : indica um novo pedido com id I (sequencial) para entrega na localidade Z
* ```CEL I``` : indica o cancelamento do pedido I
* ```DLV D``` : indica que o entregador D aceitou o próximo pedido da fila
A entrada termina com uma linha ```END```.

### Output Specification

Para cada operação da entrada, deve ser impressa uma linha como descrito a seguir.

Para cada comando NEW I Z deve ser impressa uma linha

> +I W
<p> em que W corresponde ao número de pedidos em espera incluindo o pedido I.

Para cada comando CEL I deve ser impressa uma linha

> -I W
<p>em que W corresponde ao número de pedidos em espera após a remoção do pedido I.

Para cada evento DLV D deve ser impressa uma linha

> I X Y Z K
<p> em que

* ```I``` corresponde ao identificador do pedido
* ```X``` é o local atual do entregador ao aceitar o pedido
* ```Y``` é o local do restaurante onde o pedido deve ser retirado
* ```Z``` é o local de entrega do pedido
* ```K``` é a distância total percorrida percorrida na rota de entrega escolhida X-Y-Z


Sample input | Sample output
:-------------|--------------:
| 30 226 10 20                 |   
| 0 1 495                      |   
| 0 3 621                      |   
| 0 4 675                      |   
| 0 5 171                      |   
| 0 6 90                       |   
| 0 7 206                      |   
| 0 11 237                     |   
| 0 12 155                     |   
| 0 13 916                     |   
| 0 16 492                     |   
| 0 17 58                      |   
| 0 18 367                     |   
| 0 19 604                     |   
| 0 25 505                     |   
| 0 26 835                     |   
| 0 27 544                     |   
| 0 28 665                     |   
| 1 3                          |   
| 1 5 0486                     |   
| 1 7 0468                     |   
| 1 8 0235                     |   
| 1 11 0181                    |   
| 1 14 441                     |   
| 1 16 679                     |   
| 1 18 19                      |   
| 1 19 91                      |   
| 1 21 36                      |   
| 1 22 384                     |   
| 1 24 607                     |   
| 1 25 853                     |   
| 1 26 931                     |   
| 1 29 820                     |   
| 2 3 0975                     |   
| 2 4 0789                     |   
| 2 5 0577                     |   
| 2 8 0457                     |   
| 2 9 0941                     |   
| 2 10 0205                    |   
| 2 11 0552                    |   
| 2 13 622                     |   
| 2 14 599                     |   
| 2 15 112                     |   
| 2 16 459                     |   
| 2 21 596                     |   
| 2 22 388                     |   
| 2 24 55                      |   
| 2 25 613                     |   
| 2 26 811                     |   
| 2 27 557                     |   
| 3 6 0731                     |   
| 3 8 0659                     |   
| 3 12 0551                    |   
| 3 13 597                     |   
| 3 16 697                     |   
| 3 17 467                     |   
| 3 21 593                     |   
| 3 23 769                     |   
| 3 25 682                     |   
| 3 26 187                     |   
| 3 28 933                     |   
| 3 29 621                     |   
| 4 5 0867                     |   
| 4 6 0184                     |   
| 4 8 0790                     |   
| 4 9 0908                     |   
| 4 12 0368                    |   
| 4 13 805                     |   
| 4 16 391                     |   
| 4 17 168                     |   
| 4 19 79                      |   
| 4 21 755                     |   
| 4 23 413                     |   
| 4 24 96                      |   
| 4 25 122                     |   
| 4 26 90                      |   
| 4 27 841                     |   
| 4 28 178                     |   
| 4 29 302                     |   
| 5 6 0541                     |   
| 5 7 0660                     |   
| 5 10 0327                    |   
| 5 11 0712                    |   
| 5 12 0503                    |   
| 5 13 516                     |   
| 5 14 496                     |   
| 5 15 899                     |   
| 5 18 167                     |   
| 5 20 800                     |   
| 5 22 714                     |   
| 5 24 652                     |   
| 5 25 728                     |   
| 5 26 167                     |   
| 5 29 262                     |   
| 6 8 0501                     |   
| 6 11 0487                    |   
| 6 12 0479                    |   
| 6 14 200                     |   
| 6 15 570                     |   
| 6 17 324                     |   
| 6 18 1                       |   
| 6 21 889                     |   
| 6 24 221                     |   
| 6 25 178                     |   
| 6 27 178                     |   
| 6 28 84                      |   
| 7 9 0242                     |   
| 7 10 0641                    |   
| 7 14 814                     |   
| 7 18 787                     |   
| 7 19 269                     |   
| 7 20 693                     |   
| 7 22 922                     |   
| 7 23 710                     |   
| 7 24 763                     |   
| 7 27 68                      |   
| 8 9 0427                     |   
| 8 11 0473                    |   
| 8 13 971                     |   
| 8 15 51                      |   
| 8 16 722                     |   
| 8 18 392                     |   
| 8 22 942                     |   
| 8 24 884                     |   
| 8 26 496                     |   
| 8 27 73                      |   
| 9 10 0431                    |   
| 9 11 0551                    |   
| 9 12 0400                    |   
| 9 16 539                     |   
| 9 19 152                     |   
| 9 20 53                      |   
| 9 21 701                     |   
| 9 25 766                     |   
| 9 26 678                     |   
| 9 27 916                     |   
| 9 28 471                     |   
| 9 29 371                     |   
| 10 15 493                    |   
| 10 18 163                    |   
| 10 19 183                    |   
| 10 21 231                    |   
| 10 26 308                    |   
| 10 27 72                     |   
| 11 13 107                    |   
| 11 15 94                     |   
| 11 17 195                    |   
| 11 19 535                    |   
| 11 21 384                    |   
| 11 23 910                    |   
| 11 24 923                    |   
| 11 25 166                    |   
| 11 26 347                    |   
| 11 27 167                    |   
| 11 28 85                     |   
| 12 14 439                    |   
| 12 16 331                    |   
| 12 17 268                    |   
| 12 19 703                    |   
| 12 26 111                    |   
| 12 27 927                    |   
| 12 28 935                    |   
| 12 29 82                     |   
| 13 15 726                    |   
| 13 16 6                      |   
| 13 20 851                    |   
| 13 23 254                    |   
| 13 27 69                     |   
| 14 15 454                    |   
| 14 17 224                    |   
| 14 22 473                    |   
| 14 23 642                    |   
| 14 24 896                    |   
| 14 25 481                    |   
| 14 27 958                    |   
| 14 28 838                    |   
| 14 29 211                    |   
| 15 16 744                    |   
| 15 17 375                    |   
| 15 18 54                     |   
| 15 28 871                    |   
| 15 29 572                    |   
| 16 17 377                    |   
| 16 18 194                    |   
| 16 19 276                    |   
| 16 21 165                    |   
| 16 28 201                    |   
| 17 19 248                    |   
| 17 20 158                    |   
| 17 24 321                    |   
| 17 25 592                    |   
| 17 26 838                    |   
| 17 29 334                    |   
| 18 19 401                    |   
| 18 20 475                    |   
| 18 23 668                    |   
| 18 24 938                    |   
| 18 25 462                    |   
| 18 27 337                    |   
| 18 28 999                    |   
| 19 20 166                    |   
| 19 21 273                    |   
| 19 22 61                     |   
| 19 24 320                    |   
| 19 25 39                     |   
| 21 22 593                    |   
| 21 23 966                    |   
| 21 24 765                    |   
| 21 25 636                    |   
| 21 26 399                    |   
| 21 27 369                    |   
| 21 29 208                    |   
| 22 27 582                    |   
| 22 29 53                     |   
| 23 25 100                    |   
| 23 26 385                    |   
| 23 27 597                    |   
| 23 29 157                    |   
| 24 25 399                    |   
| 24 27 256                    |   
| 24 28 693                    |   
| 25 26 572                    |   
| 25 27 944                    |   
| 25 28 610                    |   
| 26 27 315                    |   
| 27 28 617                    |   
| 27 29 894                    |   
| 9 10 12 16 17 22 23 24 26 29 |   
| NEW 0 13  | +0 1            
| NEW 1 7   | +1 2            
| NEW 2 18  | +2 3            
| NEW 3 18  | +3 4            
| NEW 4 27  | +4 5            
| NEW 5 20  | +5 6            
| NEW 6 19  | +6 7            
| NEW 7 27  | +7 8            
| NEW 8 6   | +8 9            
| NEW 9 8   | +9 10           
| DLV 0     | 0 9 9 13 379    
| NEW 10 5  | +10 10          
| NEW 11 27 | +11 11          
| NEW 12 21 | +12 12          
| NEW 13 18 | +13 13          
| DLV 16    | 1 9 9 7 242     
| DLV 14    | 2 9 9 18 262    
| NEW 14 4  | +14 12          
| DLV 2     | 3 9 9 18 262    
| DLV 6     | 4 9 9 27 310    
| CEL 5     | -5 9            
| DLV 3     | 6 9 9 19 152    
| NEW 15 20 | +15 9           
| NEW 16 20 | +16 10          
| NEW 17 7  | +17 11          
| CEL 15    | -15 10          
| CEL 13    | -13 9           
| NEW 18 14 | +18 10          
| NEW 19 20 | +19 11          
| NEW 20 19 | +20 12          
| DLV 14    | 7 18 10 27 235  
| NEW 21 25 | +21 12          
| DLV 10    | 8 9 9 6 263     
| NEW 22 7  | +22 12          
| DLV 8     | 9 9 9 8 367     
| NEW 23 20 | +23 12          
| DLV 14    | 10 27 10 5 399  
| NEW 24 14 | +24 12          
| NEW 25 5  | +25 13          
| DLV 5     | 11 9 9 27 310   
| DLV 3     | 12 19 22 21 249 
| NEW 26 6  | +26 12          
| NEW 27 11 | +27 13          
| DLV 3     | 14 21 22 4 328  
| NEW 28 21 | +28 13          
| DLV 7     | 16 9 9 20 53    
| NEW 29 19 | +29 13          
| DLV 7     | 17 20 9 7 295   
| CEL 20    | -20 11          
| NEW 30 21 | +30 12          
| DLV 16    | 18 7 17 14 488  
| NEW 31 6  | +31 12          
| NEW 32 13 | +32 13          
| DLV 9     | 19 9 9 20 53    
| NEW 33 11 | +33 13          
| DLV 4     | 21 9 9 25 191   
| DLV 7     | 22 7 10 7 280   
| NEW 34 6  | +34 12          
| NEW 35 4  | +35 13          
| NEW 36 13 | +36 14          
| NEW 37 2  | +37 15          
| CEL 35    | -35 14          
| DLV 15    | 23 9 9 20 53    
| DLV 2     | 24 18 17 14 373 
| DLV 1     | 25 9 9 5 429    
| DLV 17    | 26 9 9 6 263    
| NEW 38 28 | +38 11          
| NEW 39 2  | +39 12          
| NEW 40 6  | +40 13          
| DLV 2     | 27 14 17 11 419 
| DLV 13    | 28 9 9 21 279   
| NEW 41 6  | +41 12          
| DLV 0     | 29 13 16 19 282 
| DLV 4     | 30 25 22 21 288 
| DLV 4     | 31 21 17 6 352  
| CEL 36    | -36 8           
| DLV 4     | 32 6 16 13 201  
| CEL 34    | -34 6           
| DLV 13    | 33 21 16 11 278 
| CEL 37    | -37 4           
| NEW 42 1  | +42 5           
| NEW 43 14 | +43 6           
| NEW 44 20 | +44 7           
| DLV 19    | 38 9 9 28 347   
| NEW 45 28 | +45 7           
| DLV 2     | 39 11 24 2 316  
| NEW 46 14 | +46 7           
| NEW 47 8  | +47 8           
| NEW 48 6  | +48 9           
| NEW 49 20 | +49 10          
| NEW 50 27 | +50 11          
| NEW 51 27 | +51 12          
| NEW 52 0  | +52 13          
| DLV 15    | 40 20 17 6 306  
| DLV 0     | 41 19 22 6 233  
| NEW 53 19 | +53 12          
| NEW 54 7  | +54 13          
| NEW 55 25 | +55 14          
| NEW 56 8  | +56 15          
| CEL 43    | -43 14          
| DLV 2     | 42 2 24 1 295   
| DLV 19    | 44 28 17 20 390 
| DLV 15    | 45 6 17 28 380  
| DLV 7     | 46 7 17 14 488  
| DLV 17    | 47 6 10 8 309   
| DLV 19    | 48 20 17 6 306  
| DLV 18    | 49 9 9 20 53    
| DLV 18    | 50 20 9 27 363  
| DLV 18    | 51 27 10 27 144 
| DLV 1     | 52 5 17 0 287   
| DLV 6     | 53 27 10 19 255 
| DLV 10    | 54 6 10 7 304   
| DLV 0     | 55 6 22 25 272  
| DLV 9     | 56 20 17 8 412  
