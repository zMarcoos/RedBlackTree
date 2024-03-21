#ifndef TREE_RED_BLACK

#define true 1
#define false 0

typedef enum Color {RED, BLACK} Color;

typedef struct Node {
  int key;
  Color color;
  struct Node *left, *right, *parent;
} Node;

typedef struct Tree {
  Node *root;
} Tree;

Node *startNode(int key);
Tree *startTree();
int equals(Node *node, Node *otherNode);
Node *search(Node *node, int key);
Node *minimum(Node *node);

void moveParent(Tree *tree, Node *nodeU, Node *nodeV);
void leftRotate(Tree *tree, Node *node);
void rightRotate(Tree *tree, Node *node);
void insertFixup(Tree *tree, Node *node);
void insert(Tree *tree, int key);
void deleteFixup(Tree *tree, Node *node);
void delete(Tree *tree, int key);

Node *sibbling(Node *node);

int verifyNode(Node *node);
int blackHeight(Node *node);
int isRedBlackTree(Node *node);
void printTree(Node *node);
void treeReport(Tree *tree, int treeIndex);

#endif