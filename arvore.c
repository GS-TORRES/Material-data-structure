#include <stdio.h>
#include <stdlib.h>
#include "f_arvore.h"

int main(int argc, char const *argv[]) {
  node *a;
  node *tree = makeNode(1);
  a = addLeft(addLeft(tree, 2), 3);
  a = addRight(left(tree), 4);
  a = addLeft(addRight(tree, 5), 6);
  a = addRight(right(tree), 7);
  // 28
  // a = addRight(left(right(tree)), 100);
  // a = addLeft(left(right(tree)), 200);
  a = addRight(right(right(tree)), 1000);
  // a = addRight(right(right(right(tree))), 100);

  printf("\n Pre Ordem: ");
  preOrdem(tree);
  printf("\n\n");
  printf("\n Em Ordem: ");
  EmOrdem(tree);
  printf("\n\n");
  printf("\n Pos Ordem: ");
  posOrdem(tree);
  printf("\n\n");

  printf("\n Level: %d \n", level(tree));
  printf("\n Qtd No: %d \n", qtdNode(tree));
  printf("\n Maior: %d\n", maiorInfo(tree));
  printf("\n Soma: %d\n", somaTree(tree));

  printf("\n Altura: %d\n", depthTree(tree));

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

  if(searchByValue(tree, 7)){
    printf("\n Valor 7 Encontrado\n");
  }else{
    printf("\n Valor 7 nao Encontrado\n");
  }

  if(searchByValue(tree, 9)){
    printf("\n Valor 9 Encontrado\n");
  }else{
    printf("\n Valor 9 nao Encontrado\n");
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
if(father(no) == NULL) return 0;
  return left(father(no)) == no;
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

void depth(node *no, int *altura){
  if(father(no) == NULL){
    *altura = 0;
  }
  if(level(no) > *altura){
    *altura = level(no);
  }
  if(right(no) != NULL){
    depth(right(no), altura);
  }
  if(left(no) != NULL){
    depth(left(no), altura);
  }
}

int depthTree(node *no){
  int altura;
  depth(no, &altura);
  return altura;
}

void somatorio(node *no, int *soma){
  *soma = *soma + info(no);
  if(right(no) != NULL){
    somatorio(right(no), soma);
  }
  if(left(no) != NULL){
    somatorio(left(no), soma);
  }
}

int somaTree(node *no){
  int soma = 0;
  somatorio(no, &soma);
  return soma;
}

int searchByValue(node *no, int value){
  if(info(no) == value){
    return 1;
  }
  if(right(no) != NULL){
    return searchByValue(right(no), value);
  }
  if(left(no) != NULL){
    return searchByValue(left(no), value);
  }
  return 0;
}
