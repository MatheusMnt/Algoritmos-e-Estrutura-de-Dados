#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    long long C;
    int T;
} node;

typedef struct{
    int qtd_node;
    node * vetor;
}cel;

int binary_search(node * vetor, int tam_vetor, int T_find){
    int l = 0;
    int r = tam_vetor-1;

    while (l <= r){
        int m = (l + r) / 2;
        if (T_find == vetor[m].T){
            return m;
        } else if (T_find < vetor[m].T){
            r = m -1;
        }else{
            l = m + 1;
        }
    }
    return -1; 
}

int main()
{   

    //valores inciais 
    int M; //tamanho incial da tabela
    float Lmax; //capacidade máxima da tabela
    scanf("%d %f", &M, &Lmax);
    char op[4];// operação a ser executada (string)

    //declara a hashtable inicial
    cel * hashtable = (cel *)malloc(sizeof(cel) * M);
    cel * n_hash;
    //preenche os veotres com null
    for (int i = 0; i < M; i++){
        hashtable[i].vetor = NULL;
        hashtable[i].qtd_node = 0;
    }

    float L = 0;

    do{
        scanf(" %s", op);

        if(strcmp(op, "NEW") == 0){
            int pos;
            node new;
            scanf("%d %lld", &new.T, &new.C);
            
            //se a média de nós pelo tamanho da tabela > capacidade maxima
            if((L / M) > Lmax){//ReHashing
                
                //novo tamanho da tablea
                int New_M = (2 * M) + 1;

                //nova tabela 
                n_hash = (cel *)malloc(sizeof(cel) * New_M);
                
                //preenche a tabela com valores inciais
                for (int i = 0; i < New_M; i++){
                    n_hash[i].vetor = NULL;
                    n_hash[i].qtd_node = 0;
                }

                //para cada elemento da table aoriginal
                for(int a = 0; a < M; a++){
                    
                    //acesse o vetor associado 
                    for(int b = 0; b < hashtable[a].qtd_node; b++){

                        //nova poscao eh T mod New M
                        pos = (hashtable[a].vetor[b].T % New_M);

                        //aloca um novo vetor 
                        n_hash[pos].vetor = (node *)realloc(n_hash[pos].vetor, sizeof(node) * (n_hash[pos].qtd_node + 1));
                        //copia os dados da antiga tablea para a nova 
                        n_hash[pos].vetor[n_hash[pos].qtd_node].T = hashtable[a].vetor[b].T;
                        n_hash[pos].vetor[n_hash[pos].qtd_node].C = hashtable[a].vetor[b].C;
                        n_hash[pos].qtd_node++;
                    }
                    //libera o vetor da antiga tabela 
                    free(hashtable[a].vetor);
                }

                //ordena o vetor na nova tabela 
                //Algoritmo: BubbleSort 
                node aux;
                for(int i = 0; i < New_M;i++){
                for(int j = 0; j < n_hash[i].qtd_node;j++){
                    for(int k = j + 1; k < n_hash[i].qtd_node; k++){
                        if(n_hash[i].vetor[k].T < n_hash[i].vetor[j].T){

                            aux.T = n_hash[i].vetor[k].T;
                            aux.C = n_hash[i].vetor[k].C;

                            n_hash[i].vetor[k].T = n_hash[i].vetor[j].T;
                            n_hash[i].vetor[k].C = n_hash[i].vetor[j].C;

                            
                            n_hash[i].vetor[j].T = aux.T;
                            n_hash[i].vetor[j].C = aux.C;

                        }
                    }
                }
                   
                }
                //libera o ponteiro da antiga tabela 
                free(hashtable);
                
                //o ponteiro da antiga tabela agora aponta para a nova tabela 
                hashtable = n_hash;

                //o ponteiro que apontava para a nova tabela agora aponta para NULL
                n_hash = NULL;

                //o novo tamanho da tabela é New M
                M = New_M;
            }

            //calcula a posicao para insercao
            pos = new.T % M;
            //INSERCAO
            hashtable[pos].vetor = (node *)realloc(hashtable[pos].vetor, sizeof(node) * (hashtable[pos].qtd_node + 1));
            hashtable[pos].vetor[hashtable[pos].qtd_node].T = new.T;
            hashtable[pos].vetor[hashtable[pos].qtd_node].C = new.C;
            hashtable[pos].qtd_node++;
            
            //incrementa o numero de nós totais
            L++; 

            //pritna a posicao em que foi inserido e a quantidade de nós presentes
            printf("%d %d\n", pos, hashtable[pos].qtd_node);
        
        }else if (strcmp(op, "QRY") == 0){

            //Recebe o Timestramp a ser procurado
            int T_find;
            scanf(" %d", &T_find);

            //calcula posição em que ele vai estar na tabela
            int pos = T_find % M;
            //realiza busca binaria para descobrir a posicao no veotr associado
            int pos_find = binary_search(hashtable[pos].vetor, hashtable[pos].qtd_node, T_find);
            
            //se o T_find nao esta presente no vetor, retorna -1
            if (pos_find == -1){
                printf("-1 -1\n");
            }else{
                //caso contrario print o IP do cliente e a posicao do vetor que esta associado
                printf("%lld %d\n", hashtable[pos].vetor[pos_find].C, pos_find);
            }
        }
    }while (strcmp(op, "END") != 0);
    return 0;
}
