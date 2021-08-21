typedef struct nodeItem{
  int info;
  struct nodeItem *next;
  struct nodeItem *prev;
} node;

typedef struct {
  node *first;
  node *last;
} CList;

int infoNode(node* l);

CList *makeList();

node *newNode(int value);

int lengthList(CList *list);

void insertNode(CList *list, int value, int pos);

node *searchByPosition(CList *list, int pos);

int searchByValue(CList *list, int value);

void delByPosition(CList *list, int pos);

void delByValue(CList *list, int value);

void delList(CList *list);

int isListEmpty(CList* list);

void showList(CList* list);
