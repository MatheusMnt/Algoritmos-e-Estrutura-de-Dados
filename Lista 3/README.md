# Cache

## Descrição do problema





Uma cache é uma memória temporária que armazena itens utilizados numa determinada aplicação ou sistema. Uma característica desejável nesse tipo de memória é que ela deve permitir um acesso rápido a itens mais frequentemente utilizados, em comparação com itens menos utilizados. Para se obter esse comportamento, diversas heurísticas podem ser empregadas, dependendo da aplicação. Uma das estratégias frequentemente empregadas é a política do Mais Recentemente Utilizado - MRU. Nessa heurística, supõe-se que um item acessado recentemente tem maior chance de voltar a ser utilizado no futuro próximo e, assim sendo, é armazenado de forma a que o acesso a ele seja favorecido.

Uma estrutura de dados que pode ser utilizada como uma espécie de memória cache é a Splay tree (ST). Uma ST é uma árvore de busca binária auto-organizável em que o item mais recentemente acessado é encontrado na raiz. As três principais operações da Splay Tree são as seguintes:

Busca find(X): localiza o elemento X seguindo a regra de uma BST comum e, em seguida, move-o para a raiz.
Inserção insert(X): inserve o elemento X numa folha, como numa BST comum e, em seguida, move-o para a raiz.
Remoção delete(X): localiza e remove o item X como numa BST comum e, em seguida move o nó pai de X para a raiz, caso ele exista.
A operação de mover um nó X mara a raiz, splay(X), é executada com o auxílio de rotações. Mais especificamente, considere o (único) caminho de X até a raiz. O objetivo é fazer o X subir um nível por vez ao longo desse caminho até chegar à raiz. As rotações necessárias são determinadas posição do nó X em relação ao seu nó pai P. Se X é o filho à esquerda de P, i.e. X=P.left, então é necessário efetuar uma rotação à direita em P. Caso contrário, se X=P.right, efetua-se uma rotação à esquerda em P. Repare que, a cada rotação, X "toma o lugar" do seu pai e, portanto, sobe um nó no caminho até a raiz. Por exemplo, considere o splay do nó X=5 na árvore abaixo. A cada passo, a rotação à esquerda (L) ou à direita (R) está indicada junto ao nó em que ocorre.


```
       2                2                  2             2(L)      -->        5          
      / \             /   \               / \             / \               /    \
     1   8           1     8             1   8(R)  -->   1   5             2      8
    /   / \         /     / \           /   / \         /   / \           / \    / \
   0   6   9       0  (R)6   9   -->   0   5   9       0   4   8         1   4  6   9
      / \               / \               / \             /   / \       /   /    \
  (L)4   7    -->      5   7             4   6           3   6   9     0   3      7    
    / \               /                 /     \               \
   3   5             4                 3       7               7
                    /
                   3
```

<em> Você deverá implementar uma cache de inteiros baseada numa Splay Tree. </em>

### Input Specification <p>
A entrada é constituída por várias linhas, cada uma contendo uma operação numa das formas a seguir.

* ``` FND X ``` : localiza na ST o nó de valor X
* ``` INS X ``` : insere na ST um nó de valor X
* ``` DEL X ``` : remove da ST um nó de valor X

A entrada termina com uma linha <br>
> END

Notes:
* A Splay Tree NÃO deve conter elementos repetidos.
* A remoção de um nó com dois filhos deve ser efetuada como explicado em aula, ou seja, substituindo o valor do nó pelo seu sucessor, i.e., o menor nó da subárvore à direita.

### Output Specification

Para cada operação da entrada, deve ser impressa uma linha de saída como especificado a seguir.

Para cada comando FND X ou DEL X, deve ser impressa uma linha com um inteiro

> D

em que D correponde à profundidade do nó em que o elemento X for originalmente encontrado na árvore antes de qualquer modificação. A profundidade da raiz é 0, a dos filhos da raiz é 1, dos netos 2, e assim sucessivamente. Caso o X não seja encontrado, D deve correponder à quantidade de nós visitados no caminho da raiz até a folha percorrido pela consulta, e a árvore não sofre nenhuma alteração. Na árvore inicial do exemplo acima, caso procurássemos X=10, teríamos D=3 (nós 2, 8, 9).

Para cada comando INS X, deve ser impressa uma linha com um inteiro

> D

em que D correponde à profundidade da folha em que X foi originalmente inserido na árvore antes do splay. Caso a árvore já possua um valor X, o elemento não deve ser inserido novamente. Nesse caso, essa operação é equivalente a um FND X, e deve produzir o mesmo efeito na árvore (splay do X). D corresponderá então, como acima, à profundidade original de X.

Considera-se que a árvore está originalmente vazia.



Simple input | Simple Output
:-------------|--------------:
INS 837383338	| 0
INS 837383338	| 0
INS 152447120	| 1
INS 152447120	| 0
INS 152447120	| 0
INS 883193881	| 2
INS 613925352	| 3
INS 95506803	| 2
INS 983301190	| 3
INS 385343538	| 4
INS 837383338	| 4
INS 324302212	| 4
INS 1033473116	| 3
INS 755776447	| 5
INS 755776447	| 0
INS 297956842	| 4
INS 883193881	| 5
INS 324302212	| 3
INS 584511201	| 5
INS 314779874	| 3
INS 152447120	| 3
FND 584511201	| 2
DEL 283078920	| 4
INS 772103137	| 4
DEL 95506803	| 3
INS 1048235410	| 4
DEL 613925352	| 5
DEL 883193881	| 3
INS 234644500	| 6
DEL 258461184	| 6
DEL 385343538	| 6
FND 1048235410	| 2
FND 324302212	| 1
INS 324302212	| 0
FND 342879807	| 5
DEL 1048235410	| 1
FND 652187167	| 4
INS 1005606366	| 4
DEL 152447120	| 3
DEL 602968390	| 6
FND 234644500	| 0
INS 584511201	| 5
FND 755776447	| 3
FND 506742561	| 4
DEL 297956842	| 5
INS 540903584	| 4
INS 821119582	| 6
FND 343871688	| 4
DEL 798723411	| 4
FND 837383338	| 3
INS 1048235410	| 3
INS 385343538	| 6
INS 314779874	| 1
DEL 324302212	| 2
INS 613925352	| 7
DEL 706764051	| 5
INS 608485002	| 4
DEL 314779874	| 2
INS 540903584	| 2
INS 111928259	| 3
INS 584511201	| 3
DEL 1033473116	| 6
DEL 223255378	| 6
DEL 772103137	| 7
DEL 883193881	| 4
DEL 540903584	| 3
DEL 368308204	| 5
FND 545254670	| 4
FND 915432966	| 5
FND 983301190	| 4
FND 1048235410	| 2
INS 821119582	| 5
INS 351853039	| 6
DEL 869069140	| 5
FND 204249040	| 3
FND 1048235410	| 2
INS 863849585	| 5
INS 749160577	| 7
DEL 148827790	| 4
DEL 1005606366	| 4
INS 1012044275	| 2
FND 1060669336	| 2
DEL 995462036	| 2
FND 1048235410	| 1
INS 883193881	| 5
FND 983301190	| 3
FND 431996583	| 6
DEL 151076772	| 6
INS 385343538	| 5
FND 1005606366	| 4
INS 1048235410	| 2
FND 1070907488	| 1
DEL 152447120	| 5
DEL 34121976	| 4
FND 1005606366	| 4
INS 594124236	| 7
DEL 234644500	| 4
FND 1005606366	| 5
INS 427901342	| 4
DEL 799165480	| 9
DEL 529497326	| 3
INS 385343538	| 2
FND 1005606366	| 6
DEL 772103137	| 10
INS 45065368	| 2
FND 234644500	| 4
DEL 1029169885	| 7
FND 258777316	| 4
FND 665451810	| 10
INS 772103137	| 11
FND 234644500	| 5
DEL 385343538	| 2
INS 307698734	| 5
INS 1033473116	| 5
FND 840278064	| 8
INS 552714518	| 6
DEL 896969145	| 5
FND 307698734	| 1
FND 969824504	| 6
FND 103874718	| 3
FND 307698734	| 0
DEL 613925352	| 7
INS 755776447	| 4
DEL 749160577	| 2
INS 95506803	| 4
DEL 424018431	| 6
DEL 314775194	| 6
FND 821816331	| 10
INS 1012044275	| 6
DEL 1033473116	| 1
DEL 1048235410	| 1
FND 19017528	| 3
INS 184760721	| 5
INS 752779272	| 4
INS 1048235410	| 2
FND 808522754	| 9
FND 307698734	| 4
INS 90396031	| 4
INS 608485002	| 4
INS 754099981	| 5
INS 125433690	| 7
INS 95506803	| 2
INS 837383338	| 11
FND 1033473116	| 3
INS 95506803	| 1
INS 745670119	| 6
INS 126210969	| 6
FND 512114752	| 6
FND 375039862	| 7
INS 427901342	| 5
FND 95506803	| 2
INS 948892943	| 8
INS 743163013	| 5
FND 297956842	| 6
INS 772103137	| 6
INS 152992532	| 7
INS 327370874	| 6
INS 849385251	| 6
FND 297956842	| 5
FND 423925211	| 6
FND 297956842	| 5
INS 1012044275	| 3
INS 752779272	| 7
FND 379693382	| 5
FND 948892943	| 3
FND 1005606366	| 3
INS 752779272	| 1
INS 772103137	| 3
INS 875323067	| 5
FND 442296033	| 8
FND 1005606366	| 4
FND 772103137	| 1
FND 772103137	| 0
FND 589987544	| 9
FND 385343538	| 6
FND 385343538	| 6
FND 385343538	| 6
FND 853524359	| 4
FND 745670119	| 4
FND 991322879	| 6
FND 307698734	| 3
FND 729169553	| 6
FND 265788817	| 3
FND 755776447	| 5
FND 152447120	| 5
FND 105151536	| 7
FND 152447120	| 5
FND 832788938	| 6
FND 159751208	| 4
FND 370240053	| 7
FND 948892943	| 3
FND 815977933	| 7
FND 213609137	| 5
FND 119687971	| 8
FND 107062907	| 8
FND 220511929	| 5
FND 125433690	| 6
FND 908668987	| 6
FND 837383338	| 6
FND 837383338	| 0
FND 752779272	| 5
FND 1033473116	| 5
FND 552714518	| 8
FND 29930933	| 5
FND 552714518	| 0
FND 925935170	| 6
FND 447707586	| 5
FND 45065368	| 4
FND 427901342	| 5
FND 646706907	| 6
FND 602607432	| 7
FND 427901342	| 0
FND 427901342	| 0
FND 427901342	| 0
FND 303291031	| 6
FND 427901342	| 0
FND 427901342	| 0
FND 678673949	| 6
FND 875323067	| 5
FND 326908435	| 6
END	