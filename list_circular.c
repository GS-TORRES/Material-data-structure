#include <stdio.h>
#include <stdlib.h>
#include "f_list_circular.h"



void main(){
  CList *list = makeList();
  showList(list);
  insertNode(list, 3, 1);
  showList(list);
  insertNode(list, 1, 1);
  showList(list);
  insertNode(list, 2, 2);
  showList(list);
  insertNode(list, 4, 4);
  showList(list);
  insertNode(list, 2, 2);
  insertNode(list, 2, 1);
  insertNode(list, 2, 4);
  insertNode(list, 2, 8);
  showList(list);

  printf("\n Tamanho Lista: %d\n", lengthList(list));

  printf("\n Deletando todas posicao com valor 2, encontra a posicao e deleta(um por vez)!\n");
  delByValue(list, 2);


  showList(list);


  node *aux = searchByPosition(list, 4);

  printf("\n Deletando a Lista\n");
  delList(list);


}

int infoNode(node* l){
  return l->info;
}

CList *makeList(){
  CList *circList = (CList *)malloc(sizeof(CList));
  circList->first = NULL;
  circList->last = NULL;
  return circList;
}

node *newNode(int value){
  node *n = (node *)malloc(sizeof(node));
  n->info = value;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

int lengthList(CList *list){
  node *n = list->first;
  int tam=1;
  while(n != list->last){
    n = n->next;
    tam++;
  }
  return tam;
}

void insertNode(CList *list, int value, int pos){
  printf("\n Adicionando! Valor: %d \t Pos: %d \t Local: ", value, pos);
  node *n, *ant, *prox;
  n = newNode(value);
  if(isListEmpty(list)){
    // Qdo VAZIA
    printf("VAZIA\n");
    list->first = n;
    list->last = n;
  }else if(pos == 1){
    // No inicio
    printf("INICIO\n");
    n->next = list->first;
    n->prev = list->last;
    list->first->prev = n;
    list->last->next = n;
    list->first = n;
  }else if(pos == lengthList(list)+1){
    printf("FIM\n ");
    n->next = list->first;
    n->prev = list->last;
    list->last->next = n;
    list->last = n;
  }else{
    printf("MEIO\n");
    prox = searchByPosition(list, pos);
    ant = prox->prev;
    n->next = prox;
    n->prev = ant;
    ant->next = n;
    prox->prev = n;
  }
}

node *searchByPosition(CList *list, int pos){
  node *n = list->first;
  if(pos <= lengthList(list) && pos > 0){
    while(pos > 1){
      n = n->next;
      pos--;
    }
    return n;
  }
  return NULL;
}

int searchByValue(CList *list, int value){
  int pos = 1;
  node *n = list->first;
  if(infoNode(n) == value){
    return pos;
  }else{
    while(n != list->last){
      n = n->next;
      pos++;
      if(infoNode(n) == value){
          return pos;
      }
    }
    return -1;
  }
}

void delByPosition(CList *list, int pos){
  node *n = searchByPosition(list, pos);
  if(lengthList(list) == 1){
    list->first = NULL;
    list->last = NULL;
  }else if(pos == 1){
    n->next->prev = list->last;
    list->first = n->next;
  }else if(pos == lengthList(list)){
    n->prev->next = list->first;
    list->last = n->prev;
  }else{
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  free(n);
}

void delByValue(CList *list, int value){
  while(searchByValue(list, value) != -1){
    delByPosition(list, searchByValue(list, value));
  }
}

void delList(CList *list){
  while(list->first != list->last){
    delByPosition(list, lengthList(list));
  }
  free(list);
  printf("\nLista Deletada!\n");
}

int isListEmpty(CList* list){
  return list->first == NULL;
}

void showList(CList* list){
  node *n = list->first;
  int pos=1;

  if(list->first == NULL){
    printf("\nLista VAZIA! ");
    return;
  }else{
    printf("\nLista: ");
  }

  while(pos != lengthList(list)+1){
    printf(" [%d]=[ %d ] ",pos, infoNode(n));
    n = n->next;
    pos++;
  }
  printf("\t Tamanho: %d \n", lengthList(list));
}
