typedef struct nodeItem {
  int info;
  struct nodeItem *prev;
  struct nodeItem *next;
} node;

typedef struct {
  node *first;
  node *last;
} ListDL;


int infoNode(node* l);

ListDL* makeList();

node *newNode(int value);

int lengthList(node *firstList);

void insertNode(ListDL *list, int value, int pos);

node *searchByPosition(ListDL *list, int pos);

int searchByValue(ListDL *list, int value);

void delByPosition(ListDL *list, int pos);

void delByValue(ListDL *list, int value);

void delList(ListDL *list);

int isListEmpty(ListDL* list);

void showList(ListDL* list);
