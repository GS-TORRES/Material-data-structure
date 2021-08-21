#include <stdio.h>
#include <stdlib.h>
#include "functions_list.h"

void main(){
  ListDL *list = makeList();
  showList(list);
  printf("\n Adicionando com lista Vazia\n");
  insertNode(list, 3, 1);
  showList(list);

  printf("\n Adicionando no INICIO da lista\n");
  insertNode(list, 1, 1);
  showList(list);

  printf("\n Adicionando no MEIO da lista\n");
  insertNode(list, 2, 2);
  showList(list);
  printf("\n Adicionando no FIM da lista\n");
  insertNode(list, 4, 4);
  showList(list);
  insertNode(list, 2, 4);
  insertNode(list, 2, 2);
  insertNode(list, 2, 7);
  printf("\n Lista COMPLETA\n");
  showList(list);
  printf("\n Tamanho Lista: %d\n", lengthList(list->first));

  printf("\n Deletando todas posicao com valor 2, encontra a posicao e deleta(um por vez)!\n");
  delByValue(list, 2);


  showList(list);


  node *aux = searchByPosition(list, 2);

  printf("\n Deletando a Lista\n");
  delList(list);

//  showList(list);
}

int infoNode(node* l){
  return l->info;
}

ListDL* makeList(){
  ListDL *list = (ListDL *)malloc(sizeof(ListDL));
  list->first = NULL;
  list->last = NULL;

  return list;
}

node *newNode(int value){
  node *Item = (node *)malloc(sizeof(node));
  Item->info = value;
  Item->next = NULL;
  Item->prev = NULL;
  return Item;
}

int lengthList(node *firstList){
  if(firstList != NULL)
    return lengthList(firstList->next) + 1;
  return 0;
}

void insertNode(ListDL *list, int value, int pos){
  node *n, *ant, *prox;
  n = newNode(value);
  if(isListEmpty(list)){
    // Qdo Lista Vazia
    list->first = newNode(value);
    list->last = list->first;

  }else if(pos == 1){
    // No inicio
    list->first->prev = n;
    n->next = list->first;
    list->first = n;
  }else if(pos == lengthList(list->first)+1){
    // No fim
    list->last->next = n;
    n->prev = list->last;
    list->last = n;
  }else{
    // NO meio
    prox = searchByPosition(list, pos);
    ant = prox->prev;
    prox->prev = n;
    n->next = prox;
    ant->next = n;
    n->prev = ant;
  }
}

node *searchByPosition(ListDL *list, int pos){
  if(pos <= lengthList(list->first) && pos > 0){
    node *n = list->first;
    while(pos > 1){
      n = n->next;
      pos--;
    }
    return n;
  }
  return NULL;
}

int searchByValue(ListDL *list, int value){
  int pos = 1;
  node *n = list->first;
  if(infoNode(n) == value){
    return pos;
  }else{
    while(n->next != NULL){
      n = n->next;
      pos++;
      if(infoNode(n) == value){
          return pos;
      }
    }
    return -1;
  }
}

void delByValue(ListDL *list, int value){
  while(searchByValue(list, value) != -1){
    delByPosition(list, searchByValue(list, value));
  }
}

void delByPosition(ListDL *list, int pos){
  node *n = searchByPosition(list, pos);

  if(lengthList(list->first) == 1){
    list->first = NULL;
    list->last = NULL;
  }else if(pos == 1){
    n->next->prev = NULL;
    list->first = n->next;
  }else if(pos == lengthList(list->first)){
    n->prev->next = NULL;
    list->last = n->prev;
  }else{
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  free(n);
}

void delList(ListDL *list){
  while(list->first != NULL){
    delByPosition(list, lengthList(list->first));
  }
  free(list);
  printf("\nLista Deletada!\n");
}

int isListEmpty(ListDL* list){
  return list->first == NULL;
}

void showList(ListDL* list){
  node *n = list->first;
  int pos=1;

  if(isListEmpty(list)){
    printf("\nLista VAZIA! ");
  }else{
    printf("\nLista: ");
  }

  while(n != NULL){
    printf(" [%d]=[ %d ] ",pos, infoNode(n));
    n = n->next;
    pos++;
  }
  printf("\n");
}
