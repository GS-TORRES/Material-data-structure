#include <stdio.h>
#include <stdlib.h>
#include "f_arvore_binaria.h"
//   [10]   [15]   [14]   [16]
//                    10
//          6                    16
//     4       8          14         18
//   3  5    7  9       13  15     17  19

int main(int argc, char const *argv[]) {
  node *a;
  int vet[] = {6, 16, 4, 8, 14, 18, 3, 5, 7, 9, 13, 15, 17, 19};
  //int vet[] = {6, 16, 4, 8, 18};
  node *tree = makeNode(10);

  // int vet[] = {2, 12, 1, 4, 3, 6, 5, 10, 8, 7, 9};
  // node *tree = makeNode(11);

  for(int i=0; i<(sizeof(vet)/sizeof(int)); i++){
    insertNode(tree, vet[i]);
  }

  // a = addRight(right(right(right(tree))), 100);
  printf("\n Qtd No: %d \n", qtdNode(tree));


  if(searchByValue(tree, 10) != NULL){
    printf("\n %d Encontrado!\n", info(searchByValue(tree, 10)));
  }else{
    printf("\n Nao encontrado!\n");
  }

  printf("\n Pre Ordem: ");
  preOrdem(tree);
  printf("\n\n");

  if(isEstrita(tree)){
    printf("\n Arvore eh Estrita!\n");
  }else{
    printf("\n Arvore nao eh Estrita!\n");
  }

  if(isCompleta(tree)){
    printf("\n Arvore eh Completa!\n");
  }else{
    printf("\n Arvore nao eh Completa!\n");
  }

  delNode(tree, 10);
  delNode(tree, 19);

  printf("\n Pre Ordem: ");
  preOrdem(tree);
  printf("\n\n");

  if(isCompleta(tree)){
    printf("\n Arvore eh Completa!\n");
  }else{
    printf("\n Arvore nao eh Completa!\n");
  }
  freeTree(tree);

  return 0;
}

int info(node *no){
  return no->info;
}

node *right(node *no){
  return no->right;
}

node *left(node *no){
  return no->left;
}

node *father(node *no){
  return no->father;
}

node *brother(node *no){
  if(father(no) == NULL) return NULL;
  if(isRight(no)){
    return left(father(no));
  }else{
    return right(father(no));
  }
}

int isLeft(node *no){
  if(father(no) == NULL){
    return 0;
  }else{
    return left(father(no)) == no;
  }
}

int isRight(node *no){
  if(father(no) == NULL) return 0;
  return right(father(no)) == no;
}

node *makeNode(int value){
  node *no = (node *)malloc(sizeof(node));
  no->info = value;
  no->father = NULL;
  no->left = NULL;
  no->right = NULL;
  return no;
}


void insertNode(node *no, int value){
  if(isLeaf(no)){
    if(value > info(no)){
      addRight(no, value);
    }else{
      addLeft(no, value);
    }
  }else{
    if(value > info(no)){
      if(right(no) != NULL){
        insertNode(right(no), value);
      }else{
        addRight(no, value);
      }
    }else if(value <  info(no)){
      if(left(no) != NULL){
        insertNode(left(no), value);
      }else{
        addLeft(no, value);
      }
    }else{
      node *n = makeNode(value);
      n->right = no->right;
      n->father = no;
      no->right->father = n;
      no->right = n;
    }
  }
}

node *addLeft(node *no, int value){
  return setNodeLeft(no, makeNode(value));
}

node *setNodeLeft(node *no, node *n){
  no->left = n;
  n->father = no;
  return n;
}

node *addRight(node *no, int value){
  return setNodeRight(no, makeNode(value));
}

node *setNodeRight(node *no, node *n){
  no->right = n;
  n->father = no;
  return n;
}

  int isLeaf(node *no){
    return no->left == NULL && no->right == NULL;
  }

node *nodeRoot(node *no){
  if(father(no) != NULL){
    return nodeRoot(father(no));
  }else{
    return no;
  }
}

void preOrdem(node *no){
  if(no != NULL){
    printf(" [%d]", info(no));
    preOrdem(left(no));
    preOrdem(right(no));
  }
}

void EmOrdem(node *no){
  if(no != NULL){
    EmOrdem(left(no));
    printf(" [%d]", info(no));
    EmOrdem(right(no));
  }
}

void posOrdem(node *no){
  if(no != NULL){
    posOrdem(left(no));
    posOrdem(right(no));
    printf(" [%d]", info(no));
  }
}

void freeTree(node *no){
  if (!isLeaf(no)){
    if(left(no) != NULL){
      freeTree(left(no));
    }
    if(right(no) != NULL){
      freeTree(right(no));
    }
    free(no);
  }
}

int isEstrita(node *no){
  if(left(no) != NULL && right(no) != NULL){
    return isEstrita(left(no)) && isEstrita(right(no));
  }else{
    if(isLeaf(no)){
      return 1;
    }else{
      return 0;
    }
  }
}

int level(node *n){
  if(father(n) != NULL){
    return level(father(n)) + 1;
  }
  return 0;
}

void passNode(node *no, int *qtd){
  *qtd = *qtd + 1;
  if(!isLeaf(no)){
    if(left(no) != NULL){
      passNode(left(no), qtd);
    }
    if(right(no) != NULL){
      passNode(right(no), qtd);
    }
  }
}

int qtdNode(node *no){
  int qtd = 0;
  passNode(no, &qtd);
  return qtd;
}

int isCompleta(node *no){
  if(left(no) != NULL && right(no) != NULL){
    if(qtdNode(left(no)) == qtdNode(right(no))){
      return isCompleta(left(no)) && isCompleta(right(no));
    }else{
      return 0;
    }
  }else if(!isLeaf(no)){
    return 0;
  }
}

int maiorInfo(node *no){
  if(right(no) == NULL){
    return info(no);
  }else{
    return maiorInfo(right(no));
  }
}

int max(int a, int b){
  return a > b ? a : b;
}

int depth(node *no){
  if(no == NULL || isLeaf(no)){
    return 0;
  }
  return max(depth(left(no)), depth(right(no))) + 1;
}

int depthTree(node *no){
  return depth(nodeRoot(no));
}

node *searchByValue(node *no, int value){
  if(info(no) == value){
    return no;
  }
  if(value > info(no)){
    if(right(no) != NULL){
      return searchByValue(right(no), value);
    }else{
      return NULL;
    }
  }
  if(value < info(no)){
    if(left(no) != NULL){
      return searchByValue(left(no), value);
    }else{
      return NULL;
    }
  }
}

void delNode(node *tree, int value){
  node *no = searchByValue(tree, value);
  if(no != NULL){
    if(isLeaf(no)){
      if(left(father(no)) == no){
        no->father->left = NULL;
      }else{
        no->father->right = NULL;
      }
      free(no);
      printf(" Valor deletado! \n");
    }else if(no == tree){ // É a raiz
      if(left(tree) != NULL){
        tree->info = maiorInfo(left(tree));
        no = searchByValue(left(no), info(tree));
        delNode(no, info(no));
      }else{
        no = right(tree);
        tree->right = right(no);
        tree->left = left(no);
        tree->info = info(no);
        no->right = NULL;
        no->left = NULL;
        delNode(no, info(no));
      }
    }else{
      no->father = NULL;
      delNode(no, info(no));
    }
  }else{
    printf("\n Valor %d nao encontrado para deletar!", value);
    return;
  }
}
