# Contração de Arestas 

## Descrição do Problema

Grafos são estruturas multifuncionais e que permitem diversas operações entre seus vértices e arestas. Uma dessas operações é a contração de arestas, na qual uma dada aresta é contraída, unindo os dois vértices que eram ligados por ela em um só, que recebe todas as arestas ligadas aos vértices que existiam anteriormente. Mais formalmente, se uma aresta (A,B) que liga os vértices A e B é contraída, então esses dois rótulos são identificados e passam a representar um mesmo vértice no grafo. Essa aresta deixa de existir e qualquer outra aresta incidente a A ou a B passa agora a ser incidente a esse novo vértice resultante da contração.

Exemplo de contração:

```
           _____________________                               _____________________
          |                     |                             |                     |
          |                     |                             |                     |
          0 -------- 2 -------- 4                             |  .------ 2 -------- 4  
          |          |          |       contraindo (0,1)      | /        |          |   
          |          |          |     -------------------->  0=1         |          |   
          1 -------- 3 -------- 5                             | `------- 3 -------- 5      
          |                     |                             |                     |
          |_____________________|                             |_____________________|

```

Outra operação comum a realizar em grafos é encontrar a menor distância entre dois vértices, que se dá contando o menor número de arestas necessárias para se chegar de um vértice ao outro no grafo dado.

### Input Specification

A primeira linha da entrada contém dois inteiros

> V E

indicando a quantidade de vértices e arestas que existirão no grafo G, respectivamente.

As E linhas seguintes indicam quais são as arestas existentes no grafo no formato

> A B

indicando que existe uma aresta entre os vértices A e B (0 <= A, B < V). A linha seguinte contem um inteiro

>X

indicando o número de operações a serem realizadas sobre o grafo inicial G descrito anteriormente. Cada uma das X linhas que seguem contém exatamente uma operação de um dos dois tipos definidos acima, uma contração de aresta ou uma consulta de distância entre dois vértices. Uma contração de aresta tem o formato

> CTR A B
em que A e B são inteiros indicando que a aresta (A,B). Repare que 0 <= A, B < V são rótulos de vértices no grafo inicial, que já podem ter sido unidos a outros vértices por outras contrações.

Uma consulta de distância tem o formato

> DIS A B
em que A e B são inteiros indicando dois vértices do grafo G inicial.

#### Notes

* Para a operação de contração indicada por CTR A B, é garantido que a aresta a ser contraída existe no grafo G e que essa aresta não foi contraída antes.
* Para a operação de distância indicada por DIS A B, a distância que se deseja medir é a distância no grafo atual (ou seja, que leva em consideração todas as contrações anteriores a esta operação) entre os vértices que correspondem aos vértices A e B do grafo inicial G.
* Tanto nas operações DIS quanto CTR podemos ter A=B


### Output Specification

Para cada operação do tipo DIS A B (distância), deve ser impressa uma linha contendo a menor distância entre os vértices especificados. Caso não haja caminho entre os vértices, imprima uma linha

> -1
Para cada operação do tipo CTR A B (contração), deve ser impressa uma linha contendo dois inteiros

> P Q
onde

* P indica o número de vértices distintos no grafo após a contração
* Q indica o grau do vértice resultante da contração no grafo resultante, ou seja o números de vértices adjacentes a ele.
* No exemplo acima, teríamos P=5 e Q=4.



Sample Imput | Sample Output
:-------------|--------------:
20 25	|
10 13	|
7 8	|
1 17	|
16 17	|
17 19	|
1 4	|
10 14	|
8 17	|
2 8	|
16 19	|
12 15	|
3 18	|
2 9	|
7 19	|
8 11	|
8 14	|
9 11	|
2 12	|
2 18	|
4 13	|
13 14	|
1 13	|
12 16	|
0 9	|
0 12	|
63	|
DIS 18 15	|3
DIS 19 7	|1
DIS 3 15	|4
DIS 11 16	|3
DIS 0 7	   | 4
CTR 1 17	|19 5
CTR 17 19	|18 5
DIS 5 9	   | -1
DIS 10 2	|3
DIS 15 4	|4
DIS 15 16	|2
DIS 5 4	   | -1
DIS 16 11	|3
CTR 16 17	|17 5
CTR 3 18	|16 1
DIS 10 11	|3
DIS 7 16	|1
CTR 1 13	|15 6
DIS 1 12	|1
DIS 11 15	|4
DIS 6 19	|-1
DIS 13 7	|1
CTR 0 9	   | 14 3
CTR 4 13	|13 5
CTR 2 9	   | 12 4
DIS 12 4	|1
DIS 19 14	|1
DIS 13 13	|0
DIS 16 5	|-1
DIS 9 9	   | 0
DIS 1 16	|0
DIS 19 7	|1
DIS 13 15	|2
DIS 3 18	|0
DIS 18 5	|-1
DIS 5 17	|-1
DIS 2 8	   | 1
DIS 15 1	|2
DIS 12 18	|2
DIS 15 7	|3
DIS 4 0	   | 2
DIS 19 12	|1
DIS 1 5	   | -1
DIS 9 8	   | 1
DIS 11 19	|2
DIS 10 4	|1
DIS 5 18	|-1
DIS 14 14	|0
DIS 17 18	|3
DIS 8 6	   | -1
DIS 17 10	|1
DIS 15 2	|2
DIS 0 3	   | 1
DIS 0 4	   | 2
DIS 10 8	|2
DIS 6 10	|-1
DIS 3 16	|3
DIS 16 10	|1
DIS 3 19	|3
DIS 8 8	   | 0
DIS 5 17	|-1
DIS 2 12	|1
DIS 3 4	   | 3