#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int val;
  struct node *next;
} node;

typedef struct queue {
  node *head;
  node *tail;
} queue;

node *list_insert(node *cur, int V) {
  // printf("entrei no insert");
  node *new = malloc(sizeof(node));
  new->val = V;
  new->next = cur->next;
  cur->next = new;
  return cur;
}

node *list_delete(node *cur) {
  node *p;
  p = (cur->next);
  cur->next = p->next;
  free(p);
  return cur;
}

int list_find(node * head, int v){
  //printf("entrei no list_find\n");
  int iguais = 0;
  node * cur = head;
  while(cur->next != NULL){
    //printf("cur->next->val = %d\n", cur->next->val );
    if(cur->next->val == v){
      iguais++;
    }
    cur = cur->next;
  }
  return iguais;
}


node *deQueue(node * head, node ** tail, int * v) {
  *v = head->next->val;
  head = list_delete(head);
  if(head->next == NULL){
    *tail = head;
  }
  return head;
}

node * EnQueue(node * tail, int v){
  tail = list_insert(tail, v);
  return tail->next;
}

queue * criaFila(void){
  queue * nova = (queue*) malloc (sizeof(queue));
  nova->head = (node*) malloc (sizeof(node));
  nova->head->val = -5;
  nova->head->next = NULL;
  nova->tail = nova->head;
  return nova;
}

int shortest_path(node * grafo, int num_Vert, int origem, int destino) {
  
  int D[num_Vert];
  for(int i = 0; i < num_Vert; i++){
    D[i] = 99999;
  }

  queue * nova = criaFila();
  if (nova == NULL) {
    printf("Falha alocação Fila");
    exit(-1);
  }

  int inicio = grafo[origem].val;
  int final = grafo[destino].val;
  
  nova->tail = EnQueue(nova->tail, inicio);
  //printf("consegui fazer o enqueue com %d na origem\n", origem);
  D[inicio] = 0;

  while (nova->head != nova->tail) {
    
    int u;
    nova->head = deQueue(nova->head, &nova->tail, &u);
    
   // printf("u = %d, lista[u].val = %d\n", u, grafo[u].val);
    node * e = malloc(sizeof(node));
    e  = grafo[u].next;
    
    //printf("grafo[u]->next->val = %d\n", e->val);
    
    while (e != NULL) {
      int v = e->val;
      //printf("v = %d\n", e->val);
      if (D[v] == 99999) {
        //printf("antes: D[v] = %d e D[u] = %d\n", D[v], D[u]);
        D[v] = D[u] + 1;
         //printf("depois: D[v] = %d e D[u] = %d\n", D[v], D[u]);
        nova->tail = EnQueue(nova->tail, v);
      }
      if(v == final){
        return D[v];
      }
      e = e->next;
    }
  }
  
  if (D[final] == 99999) {
    return -1;
  }else {
    return D[final];
  }
}
void cpr(node * grafo, int VertA, int VertB,int * qtd_vert, int num_vert) {
  
  node *auxA = &grafo[VertA];
  node *auxB = &grafo[VertB];

  int RepresentanteA = auxA->val;
  int RepresentanteB = auxB->val;

  int grau = 0;
  int dist = shortest_path(grafo, num_vert, VertA, VertB);
  
  if(RepresentanteA != RepresentanteB && dist == 1){
    node * aux1 = &grafo[RepresentanteA];
    //node * head = aux1;
    node * aux2 = &grafo[RepresentanteB];
  
    (*qtd_vert)--;
  
    while(aux2->next != NULL){
      int insert = list_find(aux1, aux2->next->val);
      if(insert == 0 && ((aux2->next->val != RepresentanteB) && (aux2->next->val != RepresentanteA))){
        aux1 = list_insert(aux1, aux2->next->val);
      }
      aux2 = aux2->next;
    }
  
    for(int i = 0; i < num_vert; i++){
      node * aux = &grafo[i];
      while(aux != NULL){
        
        if(aux->val == RepresentanteB){
          aux->val = RepresentanteA;
        }
        
          aux = aux->next;
      }
    }

    for(int i = 0; i < num_vert; i++){
      node * aux = &grafo[i];
      while(aux != NULL){
        int findA = list_find(aux, RepresentanteA);
        if(findA > 1 && aux->next->val == RepresentanteA){
          aux = list_delete(aux);
        }
          aux = aux->next;
      }
    }
    
    grafo[RepresentanteB].val = RepresentanteA;
    grafo[RepresentanteB].next = NULL;

    node * aux3 = &grafo[RepresentanteA];
    while( aux3->next != NULL){
      grau++;
      if(aux3->next->val == RepresentanteA || aux3->next->val == RepresentanteB){
        grau--;
        aux3 = list_delete(aux3);
      }else{
        aux3 = aux3->next;
      }
    //printf("%d %d\n", (*qtd_vert), grau);
    }
  }else{
    //int grau = 0;
    node * aux3 = &grafo[RepresentanteA];
    while(aux3->next != NULL){
      grau++;
      if(aux3->next->val == RepresentanteA || aux3->next->val == RepresentanteB){
        grau--;
        aux3 = list_delete(aux3);
      }else{
        aux3 = aux3->next;
      }
    }
  }
  printf("%d %d\n", (*qtd_vert), grau);
}

void print_Grafo(node *lista, int num_vertices) {
  for (int i = 0; i < num_vertices; i++) {
    printf("\no vertice %d tem ligacao com: ", lista[i].val);
    {
      node *aux = &lista[i];
      while (aux->next != NULL) {
        printf("%d ", aux->next->val);
        aux = aux->next;
      }
    }
  }
  printf("\n");
}


int main(void) {

  int vertices; // vertivces
  int arestas;  // arestas
  // printf("iniciei");

  scanf("%d %d", &vertices, &arestas);
  // printf("%d e %d", vertices, arestas);

  node *grafo = (node *)malloc(sizeof(node) * vertices);
  if (grafo == NULL) {
    printf("Erro de Alocação");
    exit(-1);
  }

  for (int i = 0; i < vertices; i++) {
    // printf("entrei no 1o loop");
    grafo[i].val = i;
    grafo[i].next = NULL;
    // printf("%d", grafo[i].val);
  }

  for (int i = 0; i < arestas; i++) {
    // printf("entrei no loop");
    int A, B;
    scanf("%d %d", &A, &B);
    node *auxA = &grafo[A];
    node *auxB = &grafo[B];
    auxA = list_insert(auxA, B);
    auxB = list_insert(auxB, A);
  }

  int num_op;
  scanf("%d", &num_op);
  char op[4];
  int numV = vertices;
  for (int i = 0; i < num_op; i++) {
    int A = -7;
    int B = -7;
    scanf(" %s %d %d", op, &A, &B);
    if (strcmp(op, "CTR") == 0) {
      //Compression(grafo, A, B, &numV, vertices);
      cpr(grafo, A, B, &numV, vertices);
      /*for(int i = 0; i < vertices; i++){
        node * aux = &grafo[i];
        while(aux->next != NULL){
          if(aux->next->val == B){
            aux->next->val = A;
          }
          aux = aux->next;
        }
      }*/
    } else if (strcmp(op, "DIS") == 0) {
      int dist = shortest_path(grafo, vertices, A, B);
      printf("%d\n", dist);
    } else if (strcmp(op, "PRT") == 0) {
      print_Grafo(grafo, vertices);
    }
  }

  return 0;
}