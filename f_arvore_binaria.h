typedef struct nodeItem{
  int info;
  struct nodeItem *father;
  struct nodeItem *left;
  struct nodeItem *right;
} node;

int info(node *no);

node *right(node *no);

node *left(node *no);

node *father(node *no);

node *brother(node *no);

int isLeft(node *no);

int isRight(node *no);

int isLeaf(node *no);

node *makeNode(int value);

void insertNode(node *no, int value);

node *addLeft(node *no, int value);

node *setNodeLeft(node *no, node *n);

node *addRight(node *no, int value);

node *setNodeRight(node *no, node *n);

node *nodeRoot(node *no);

void preOrdem(node *no);

void EmOrdem(node *no);

void posOrdem(node *no);

void freeTree(node *no);

int isEstrita(node *no);

int level(node *n);

void passNode(node *no, int *qtd);

int qtdNode(node *no);

int isCompleta(node *no);

void maior(node *no, int *m);

int maiorInfo(node *no);

int max(int a, int b);

int depth(node *no);

int depthTree(node *no);

void delNode(node *tree, int value);

node *searchByValue(node *no, int value);
