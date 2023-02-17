#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura do grafo
typedef struct node {
  int val;
  int peso;
  struct node *prox;
} node;

//strutura da heap
typedef struct bean{
  int val;
  int peso;
}bean;

node * list_insert(node * atual, int vert, int peso) {
  node * nova = (node*)malloc(sizeof(node) * 1);
  nova->val = vert;
  nova->peso = peso;
  nova->prox = atual->prox;
  atual->prox = nova;
  return atual;
}

bean * buble_up(bean * heap, int i) {
  while (i > 0 && heap[i].peso < heap[(i - 1) / 2].peso) {
    bean aux = heap[i];
    heap[i] = heap[(i - 1) / 2];
    heap[(i - 1) / 2] = aux;
    i = (i - 1) / 2;
  }
  return heap;
}

bean * heap_insert(bean heap [], int * heap_size, int V, int val, int peso) {
  int i = (*heap_size);
  heap[i].val = val;
  heap[i].peso = peso;
  //printf("entrei no Heap_insert com heap_size = %d\n", (*heap_size));
  heap = buble_up(heap, i);
  (*heap_size)++;
  return heap;
}

bean *heapify(bean *heap, int inicio, int heap_size) {
  int l = (2 * inicio) + 1;
  int r = (2 * inicio) + 2;
  int m = inicio;
  if (l < heap_size && heap[l].peso <= heap[m].peso) {
    m = l;
  }
  if (r < heap_size && heap[r].peso <= heap[m].peso) {
    m = r;
  }
  if (m != inicio) {
    bean aux = heap[m];
    heap[m] = heap[inicio];
    heap[inicio] = aux;
    heap = heapify(heap, m, heap_size);
  }
  return heap;
}

bean * heap_extract(bean * heap, int *heap_size, bean *retorno) {
    bean aux = heap[0];
    heap[0] = heap[(*heap_size) - 1];
    heap[(*heap_size) - 1] = aux;
    (*heap_size)--;
    heap = heapify(heap, 0, (*heap_size));
    (*retorno) = aux;
  return heap;
}

int * Dijkstra(node * grafo, int * dist, int num_arestas, int origem,int num_vertices) {
  //printf("entrei no Dijkstra\n");
  int flag;
  dist = (int *)malloc(sizeof(int) * num_vertices);  

  for (int i = 0; i < num_vertices; i++) {
    dist[i] = __INT_MAX__;
  }

  dist[origem] = 0;

  bean * heap = (bean *)malloc(sizeof(bean) * num_vertices);
  int heap_size = 0;

  heap = heap_insert(heap, &heap_size, num_vertices, origem, dist[origem]);

  for (int i = 0; i < num_vertices; i++){

    bean u;
    heap = heap_extract(heap, &heap_size, &u);
    node * e = grafo[u.val].prox;
    //printf("%d -> %d com dist = %d\n", origem, u.val, u.peso);

    while(e != NULL){

      int v = e->val;
      int w = e->peso;

      //printf("%d e %d vs %d e %d\n", u.val, dist[u.val], v, dist[v]);

      if(dist[u.val] + w < dist[v] || dist[v] == __INT_MAX__){
        dist[v] = dist[u.val] + w;
        //printf("%d e %d vs %d e %d\n",u.val, dist[u.val], v, dist[v]);
        flag = 0;
        for(int j = 0; j <= heap_size && flag == 0; j++){
          if(heap[j].val == v){
            heap[j].peso = dist[v];
            heap = buble_up(heap, j);
            flag = 1;
          }
        }
        if(flag == 0){
          heap = heap_insert(heap, &heap_size, num_vertices, v, dist[v]);
        }
          /*   printf("HEAP:\n");
          for(int a = 0; a < heap_size; a++){
            printf("%d: %d, %d\n", a, heap[a].val, heap[a].peso);
          }
          printf("\n");     */
      }
      e = e->prox;
    }
  }
  return dist;
}

//estrutura dos pedidos
typedef struct order {
  int id;
  int destino;
  struct order *prox;
} order;

typedef struct lista {
  order *head;
  order *tail;
  int qtd_elem;
} lista;

order *order_insert(order * atual, int id, int destino) {
  //printf("entrei no insert\n");
  order * nova = (order *)malloc(sizeof(node));
  if(nova == NULL){
    printf("erro de alocacao");
    exit(-1);
  }
  nova->id = id;
  nova->destino = destino;
  //printf("dei errado aqui\n");
  //printf("dei errado no order insert");
  nova->prox = atual->prox;
  atual->prox = nova;
  //printf("no insert : %d e %d", nova->id, nova->destino);
  return atual;
}

order *order_delete(order * atual, int * id, int * destino) {
  order * aux = atual->prox;
  atual->prox = aux->prox;
  *id = aux->id;
  *destino = aux->destino;
  aux = NULL;
  free(aux);
  return atual;
}

order * order_find(order * head, int id){
  order * aux = head;
  while(aux->prox != NULL && aux->prox->id != id){
    aux = aux->prox;
  }
  return aux;
}

order *enQueue(order * head, order * tail, int * qtd_elem, int id, int destino) {
  //printf("entrei no enQueue\n");
  tail = order_insert(tail, id, destino);
  //printf("fiz o insert\n");
  (*qtd_elem)++;
  tail = tail->prox;
  return tail;
}

order *deQueue(order * head, order * tail, int * qtd_elem, int * id, int * destino) {
  head = order_delete(head, id, destino);
  (*qtd_elem)--;
  if (head->prox == NULL) {
    tail = head;
  }
  return head;
}

typedef struct place{
    int num;
    int * distancias;
}place;


  void print_Grafo(node *lista, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
      printf("\no vertice %d tem ligacao com: ", i);
      {
        node * aux = &lista[i];
        while (aux->prox != NULL) {
          printf("(%d, %d) ", aux->prox->val, aux->prox->peso);
          aux = aux->prox;
        }
      }
    }
    printf("\n");
  }
int main(void) {

  int V, E, N, M;
  scanf("%d %d %d %d", &V, &E, &N, &M);
  //printf("peguei : %d %d %d %d", V, E, N, M);

  node * grafo = (node *)malloc(sizeof(node) * V);
  if (grafo == NULL) {
    printf("erro de alocacao");
    exit(-1);
  }

  for(int i = 0; i < V; i++){
    grafo[i].prox = NULL;
  }

  for (int i = 0; i < E; i++) {
    //printf("dei errado aqui\n");
    int vertA, vertB, peso;
    scanf(" %d %d %d", &vertA, &vertB, &peso);
    //printf("peguei %d %d %d\n", vertA, vertB, peso);
    node * auxA = &grafo[vertA];
    node * auxB = &grafo[vertB];
    auxA = list_insert(auxA, vertB, peso);
    auxB = list_insert(auxB, vertA, peso);
    //printf("%d -> %d\n", auxA->prox->val, auxB->prox->val);
  }

  int Restaurantes[N];
  for(int i = 0; i < N; i++){
    int restaurante;
    scanf(" %d", &restaurante);
    Restaurantes[i] = restaurante;
    //printf("peguei %d\n", Restaurantes[i]);
  }

  place * rest = (place *)malloc(sizeof(place) * N);
  


  //print_Grafo(grafo, V);

  for(int i = 0; i < N; i++){
    rest[i].num = Restaurantes[i];
    //printf("coloquei %d\n", rest[i].num);  
    rest[i].distancias = Dijkstra(grafo, rest[i].distancias, E, Restaurantes[i], V);
    /*printf("Restaurante %d:\nDistancia: ", i);
    for(int b = 0; b < V; b++){
      printf("%d ", rest[i].distancias[b]);
    }
    printf("\n\n");*/
  }


  int pos_entregadores[M];

  for (int i = 0; i < M; i++) {
    pos_entregadores[i] = Restaurantes[0];
  }

  char op[4];

  lista orders;
  orders.qtd_elem = 0;
  
  do {

    if(orders.qtd_elem == 0 || orders.head->prox == NULL){
      orders.head = (order *)malloc(sizeof(order) * 1);
      orders.tail = orders.head;
      //printf("fila vazia\n");
    }

    scanf(" %s", op);     
    //printf("recebi %s", op);
    if (strcmp("DLV", op) == 0) {
      /*order * aux = orders.head->prox;
      printf("Fila de Pedidos: \n");
      while(aux != NULL){
        printf("id = %d destino = %d\n", aux->id, aux->destino);
        aux = aux->prox;
      }*/
      int id, destino, entregador, origem;
      scanf(" %d", &entregador);

      orders.head = deQueue(orders.head, orders.tail, &orders.qtd_elem, &id, &destino);
      //printf("sai do deQueue com %d e %d\n", id, destino);
      origem = pos_entregadores[entregador];

      int distancia = __INT_MAX__;
      int restaurante;

      for (int i = 0; i < N; i++) {
        if (rest[i].distancias[origem] + rest[i].distancias[destino] < distancia) {
          distancia = rest[i].distancias[origem] + rest[i].distancias[destino];
          pos_entregadores[entregador] = destino;
          restaurante = rest[i].num;
        }else if (rest[i].distancias[origem] + rest[i].distancias[destino] == distancia){
            if(rest[i].num < restaurante){
              distancia = rest[i].distancias[origem] + rest[i].distancias[destino];
              pos_entregadores[entregador] = destino;
              restaurante = rest[i].num;
            }
        }
      }

      printf("%d %d %d %d %d\n", id, origem, restaurante, destino, distancia);

    } else if (strcmp("CEL", op) == 0) {
        int id;
        scanf(" %d", &id);
        int id_excluido;
        int destino;
        order * find = order_find(orders.head, id);
        order * aux = order_delete(find, &id_excluido, &destino);
        orders.qtd_elem--;    
        if(id != id_excluido){
              printf("nó errado");
        }else {
          printf("-%d %d\n",id_excluido, orders.qtd_elem);
        }
        //free(find);
        //free(aux);
        if(aux->prox == NULL){
          orders.tail = aux;
        }
    } else if (strcmp("NEW", op) == 0) {
      int id;
      int destino;
      scanf(" %d %d", &id, &destino);
      //printf("%d e %d\n", id, destino);
      orders.tail = enQueue(orders.head, orders.tail, &orders.qtd_elem, id, destino);
      //printf("adiciona %d e %d\n", orders.tail->id, orders.tail->destino);
      order * aux = orders.head->prox;
      /*printf("Fila de Pedidos: \n");
      while(aux != NULL){
        printf("id = %d destino = %d\n", aux->id, aux->destino);
        aux = aux->prox;
      }*/
      printf("+%d %d\n", id, orders.qtd_elem);
    }
  } while (strcmp("END", op) != 0);

  return 0;
}