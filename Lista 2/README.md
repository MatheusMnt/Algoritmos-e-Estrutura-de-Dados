## Descrição do Problema



Um sistema de monitoramento de redes registra as conexões recebidas por um servidor ao longo do tempo. Para cada conexão, registra-se o timestamp T (inteiro de 32bits sem sinal) do momento em que a conexão foi aceita pelo servidor e o endereço IP do cliente C além de outros dados.

Um processo de auditoria que roda em paralelo precisa consultar esporadicamente os dados de conexões recebidas em momentos específicos, indicados por seus timestamps.

Inicialmente, o registro das conexões era realizado num único arquivo de log, porém, com o aumento do tráfego, as consultas a esse arquivo passaram a ficar muito lentas. A equipe de desenvolvimento projetou então a seguinte arquitetura para agilizar as consultas. Para cada conexão, o par (T,C) (timestamp, cliente) é armazenado numa hashtable. Os demais dados da conexão são armazenados num arquivo de log específico para cada cliente C. O processo de auditoria pode então consultar essa hashtable pelo timestamp da conexão T, obter a identificação do cliente C, e então procurar os demais dados da conexão diretamente no arquivo desse cliente.

A hashtable deve usar a função de dispersão

> h(T) = T mod M 

onde T é o timestamp (único) de cada conexão (usado como chave), e M é o tamanho da tabela (inteiro ímpar). Cada posição da tabela armazena uma lista de pares (T,C) (open hashing). Cada nova conexão (T,C) a ser registrada na tabela deve ser adicionada à lista da posição h(T), de forma que estas listas estejam sempre ordenadas pelos timestamps.

Imediatamente antes de cada inserção na hashtable, o sistema verifica o seu fator de carga L e, caso esse fator seja estritamente superior (>) a um valor máximo Lmax, ocorre um rehashing para uma nova tabela de tamanho 2*M+1, tomando cuidado para que as listas da nova tabela também estejam ordenadas por timestamp. Após o rehashing, a nova conexão é registrada.

Input Specification


A entrada inicia com uma linha

> M Lmax

onde M é o tamanho inicial da hashtable e Lmax (float) é o fator de carga limite.

Seguem-se eventos numa das formas a seguir.


> NEW T C : indica uma nova conexão com timestamp T e cliente C
> QRY T : indica uma consulta do processo auditor a uma possível conexão no timestamp T

A entrada termina com uma linha

> END

Notes

O IP C de cada cliente é registrado como um inteiro de 4bytes

Exemplo:


123.231.045.101 --> 7B.E7.2D.65 --> 7BE72D65 (Hex) --> 2078748005 (Dec)


Output Specification

Para cada entrada evento NEW T C da entrada, imprimir uma linha

> I S

onde I=h(T) representa a posição final (0-based) da hashtable (eventualmente após rehashing) na qual a conexão foi inserida, e S representa a quantidade de pares (tamanho da lista) gravados nessa posição após a inserção.

Para cada evento QRY T, imprimir uma linha

>C J

onde C representa o cliente da conexão ocorrida no timestamp T e J representa a posição (0-based) do par (T,C) na lista da posição h(T) da hashtable na qual ela foi encontrada. Caso não haja nenhuma conexão registrada nesse timestamp, deve ser impressa uma linha


>-1 -1



Simple input | Simple Output
:-------------|--------------:
7 3
NEW 8 2552088320    |    1 1
NEW 12 2552088320   |    5 1
NEW 22 814388853    |    1 2
NEW 23 992702515    |    2 1
NEW 33 814388853    |    5 2
NEW 35 992702515    |    0 1
NEW 43 2552088320   |    1 3
NEW 47 3354783599   |    5 3
NEW 52 4109305985   |    3 1
NEW 62 2552088320   |    6 1
NEW 67 4109305985   |    4 1
NEW 75 327881993    |    5 4
NEW 81 28542344     |    4 2
NEW 90 1940478054   |    6 2
NEW 93 2552088320   |    2 2
NEW 100 327881993   |    2 3
NEW 105 28542344    |    0 2
NEW 111 814388853   |    6 3
NEW 117 2251439267  |    5 5
NEW 119 28542344    |    0 3
NEW 120 4109305985  |    1 4
NEW 126 28542344    |    0 4
NEW 131 1940478054  |   11 1
NEW 134 4109305985  |   14 2
NEW 143 3869091182  |    8 3
NEW 151 1940478054  |    1 1
NEW 159 2781438510  |    9 1
NEW 164 327881993   |   14 3
NEW 168 4109305985  |    3 3
NEW 174 28542344    |    9 2
NEW 182 3354783599  |    2 3
NEW 184 3725499951  |    4 1
NEW 189 4125602132  |    9 3
NEW 195 992702515   |    0 5
NEW 204 4246797368  |    9 4
NEW 214 3638383574  |    4 2
NEW 224 992702515   |   14 4
NEW 234 4246797368  |    9 5
NEW 238 401543791   |   13 2
NEW 243 1841054525  |    3 4
NEW 244 2113522543  |    4 3
NEW 249 2113522543  |    9 6
NEW 257 190885248   |    2 4
NEW 266 3869091182  |   11 2
NEW 274 2447600621  |    4 4
NEW 282 1524144875  |   12 3
NEW 286 2945265535  |    7 4
NEW 294 4273673229  |   15 1
NEW 304 2552088320  |   25 1
NEW 313 28542344    |    3 3
NEW 322 1052679968  |   12 4
NEW 325 2773631387  |   15 2
NEW 330 2447600621  |   20 1
NEW 339 4195714889  |   29 2
NEW 348 319349324   |    7 5
NEW 358 2773631387  |   17 2
NEW 367 3095927177  |   26 4
NEW 370 919093750   |   29 3
NEW 376 401543791   |    4 3
NEW 382 1494019986  |   10 2
NEW 383 1940478054  |   11 1
NEW 387 993182843   |   15 3
NEW 391 992702515   |   19 4
NEW 393 3978617334  |   21 3
NEW 397 2447600621  |   25 2
NEW 406 919093750   |    3 4
NEW 410 2113522543  |    7 6
NEW 416 2881275136  |   13 3
NEW 417 2440877302  |   14 1
NEW 422 814388853   |   19 5
NEW 432 28542344    |   29 4
NEW 440 28542344    |    6 1
NEW 449 2706880220  |   15 4
NEW 450 1524144875  |   16 2
NEW 454 1926957225  |   20 2
NEW 464 3725499951  |   30 1
NEW 474 4246797368  |    9 4
NEW 483 3869091182  |   18 4
NEW 484 379228221   |   19 6
NEW 485 919093750   |   20 3
NEW 489 3638383574  |   24 2
NEW 498 327881993   |    2 3
NEW 503 1552000874  |    7 7
NEW 507 3867193699  |   11 2
NEW 510 892067311   |   14 2
NEW 518 1524144875  |   22 2
NEW 521 2251439267  |   25 3
NEW 523 3095927177  |   27 5
NEW 524 28542344    |   28 3
NEW 528 1754250229  |    1 2
NEW 530 2781438510  |    3 5
NEW 540 1396537965  |   13 4
NEW 545 2829014658  |   18 5
NEW 553 4246797368  |   26 5
NEW 561 2119460268  |   57 3
NEW 567 114789785   |    0 3
NEW 569 2777943267  |    2 1
NEW 576 275218589   |    9 3
NEW 579 1052679968  |   12 3
NEW 580 3354783599  |   13 3
NEW 588 4139376621  |   21 1
QRY 524             |   28542344 0
NEW 593 3095927177  |   26 2
NEW 596 454100557   |   29 1
NEW 606 919093750   |   39 2
QRY 304             |   2552088320 1
NEW 614 2119460268  |   47 2
NEW 623 2901834336  |   56 3
QRY 530             |   2781438510 0
NEW 628 2773631387  |   61 3
NEW 637 2773631387  |   7 2
NEW 644 2363020848  |   14 3
QRY 518             |   1524144875 1
NEW 652 379228221   |   22 3
NEW 656 886696440   |   26 3
NEW 662 2777943267  |   32 2
NEW 671 892067311   |   41 2
QRY 122             |  -1 -1
NEW 681 2046506218  |   51 1
QRY 234             |   4246797368 0
NEW 691 3869091182  |   61 4
NEW 697 4246797368  |    4 3
NEW 703 3553670342  |   10 2
NEW 704 1396537965  |   11 1
NEW 713 892067311   |   20 2
NEW 722 919093750   |   29 2
NEW 723 3362048454  |   30 3
NEW 725 1368816966  |   32 3
NEW 733 3978617334  |   40 1
NEW 736 19304273    |   43 4
QRY 489             |   3638383574 2
QRY 93              |   2552088320 0
NEW 755 401543791   |   62 4
NEW 757 2881275136  |    1 1
NEW 759 28542344    |    3 2
NEW 763 327881993   |    7 3
NEW 771 1940478054  |   15 4
NEW 772 542424540   |   16 1
NEW 777 3936639032  |   21 2
QRY 420             |  -1 -1
NEW 787 3354908551  |   31 1
NEW 795 2829939388  |   39 3
NEW 799 3865600939  |   43 5
NEW 801 992702515   |   45 2
NEW 811 919093750   |   55 3
QRY 78              |  -1 -1
NEW 814 2251439267  |   58 2
NEW 816 1373340970  |   60 2
NEW 824 4109305985  |    5 4
NEW 834 3354783599  |   15 5
NEW 835 2251439267  |   16 2
QRY 52              |   4109305985 0
NEW 847 1841054525  |   28 2
QRY 847             |   1841054525 1
NEW 854 1980445736  |   35 3
NEW 860 2969604979  |   41 3
QRY 460             |  -1 -1
QRY 485             |   919093750 1
QRY 237             |  -1 -1
NEW 881 825257068   |   62 5
NEW 883 2700968992  |    1 2
NEW 888 1524144875  |    6 3
NEW 889 3553670342  |    7 4
NEW 893 275218589   |   11 2
NEW 899 1754250229  |   17 3
QRY 824             |   4109305985 3
NEW 908 825257068   |   26 4
NEW 916 1906100118  |   34 2
NEW 921 2134159845  |   39 4
NEW 923 3231106216  |   41 4
NEW 929 83799508    |   47 3
NEW 935 1368816966  |   53 1
QRY 111             |   814388853 0
NEW 947 2040021274  |    2 2
NEW 951 4195714889  |    6 4
NEW 957 176529667   |   12 4
NEW 961 4246797368  |   16 3
NEW 967 542424540   |   22 4
QRY 111             |   814388853 0
NEW 973 3978298340  |   28 3
QRY 120             |   4109305985 0
QRY 111             |   814388853 0
NEW 979 2251439267  |   34 3
NEW 982 2914089597  |   37 2
NEW 989 1926957225  |   44 3
QRY 733             |   3978617334 0
NEW 1002 2113522543 |   57 4
QRY 243             |   1841054525 1
NEW 1008 3311361186 |    0 4
NEW 1009 1368816966 |    1 3
NEW 1014 418866054  |    6 5
QRY 759             |   28542344 1
NEW 1022 392281481  |   14 4
NEW 1031 892067311  |   23 3
NEW 1038 454100557  |   30 4
QRY 432             |   28542344 2
QRY 883             |   2700968992 1
NEW 1053 3311361186 |   45 3
NEW 1055 4109305985 |   47 4
NEW 1061 379228221  |   53 2
END