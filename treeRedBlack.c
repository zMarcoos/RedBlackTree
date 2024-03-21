#include <stdio.h>
#include <stdlib.h>
#include "treeRedBlack.h"

Node EXTERNAL_NODE = {-1, BLACK, NULL, NULL, NULL};

Node *startNode(int key) {
  Node *node = (Node*) malloc(sizeof(Node));
  node->key = key;
  node->color = RED;
  node->left = &EXTERNAL_NODE;
  node->right = &EXTERNAL_NODE;
  node->parent = &EXTERNAL_NODE;
  return node;
}

Tree *startTree() {
  Tree *tree = (Tree*) malloc(sizeof(Tree));
  tree->root = &EXTERNAL_NODE;
  return tree;
}

int equals(Node *node, Node *otherNode) {
  return (node->key == otherNode->key) && (node->color == otherNode->color);
}

Node *search(Node *root, int key) {
  if (equals(root, &EXTERNAL_NODE) || key == root->key) {
    return root;
  }

  Node *left = search(root->left, key);
  if (!equals(left, &EXTERNAL_NODE)) return left;

  return search(root->right, key);
}

Node *minimum(Node *node) {
  while (!equals(node->left, &EXTERNAL_NODE)) {
    node = node->left;
  }

  return node;
}

void moveParent(Tree *tree, Node *nodeU, Node *nodeV) {
  if (nodeU->parent == &EXTERNAL_NODE) {
    tree->root = nodeV;
  } else {
    if (nodeU == nodeU->parent->left) {
      nodeU->parent->left = nodeV;
    } else {
      nodeU->parent->right = nodeV;
    }
  }

  nodeV->parent = nodeU->parent;
}

void leftRotate(Tree *tree, Node *node) {
  Node *pointerY = node->right;
  node->right = pointerY->left;

  if (pointerY->left != &EXTERNAL_NODE) {
    pointerY->left->parent = node;
  }

  pointerY->parent = node->parent;

  if (node->parent == &EXTERNAL_NODE) {
    tree->root = pointerY;
  } else {
    if (node == node->parent->left) {
      node->parent->left = pointerY;
    } else {
      node->parent->right = pointerY;
    }
  }

  pointerY->left = node;
  node->parent = pointerY;
}

void rightRotate(Tree *tree, Node *node) {
  Node *pointerY = node->left;
  node->left = pointerY->right;

  if (pointerY->right != &EXTERNAL_NODE) {
    pointerY->right->parent = node;
  }

  pointerY->parent = node->parent;

  if (node->parent == &EXTERNAL_NODE) {
    tree->root = pointerY;
  } else {
    if (node == node->parent->right) {
      node->parent->right = pointerY;
    } else {
      node->parent->left = pointerY;
    }
  }

  pointerY->right = node;
  node->parent = pointerY;
}

void insertFixup(Tree *tree, Node *node) {
  Node *pointerY = &EXTERNAL_NODE;

  while (node->parent->color == RED) {
    if (node->parent == node->parent->parent->left) {
      pointerY = node->parent->parent->right;

      if (pointerY->color == RED) {
        node->parent->color = BLACK;
        pointerY->color = BLACK;
        node->parent->parent->color = RED;

        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;

          leftRotate(tree, node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;

        rightRotate(tree, node->parent->parent);
      }
    } else {
      pointerY = node->parent->parent->left;

      if (pointerY->color == RED) {
        node->parent->color = BLACK;
        pointerY->color = BLACK;
        node->parent->parent->color = RED;

        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;

          rightRotate(tree, node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;

        leftRotate(tree, node->parent->parent);
      }
    }
  }

  tree->root->color = BLACK;
}

void insert(Tree *tree, int key) {
  Node *node = startNode(key);
  Node *pointerY = &EXTERNAL_NODE;
  Node *pointerX = tree->root;

  while (pointerX != &EXTERNAL_NODE) {
    pointerY = pointerX;

    pointerX = node->key < pointerX->key ? pointerX->left : pointerX->right;
  }

  node->parent = pointerY;

  if (pointerY == &EXTERNAL_NODE) {
    tree->root = node;
  } else {
    if (node->key < pointerY->key) {
      pointerY->left = node;
    } else {
      pointerY->right = node;
    }
  }

  node->left = &EXTERNAL_NODE;
  node->right = &EXTERNAL_NODE;
  node->color = RED;

  insertFixup(tree, node);
}

//funcao original
/*void deleteFixup(Tree *tree, Node *node) {
  Node *sibbling;

  while (node != tree->root && node->color == BLACK) {
    if (node == node->parent->left) {
      sibbling = node->parent->right;

      if (sibbling->color == RED) {
        sibbling->color = BLACK;
        node->parent->color = RED;

        leftRotate(tree, node->parent);

        sibbling = node->parent->right;
      }

      if (sibbling->left->color == BLACK && sibbling->right->color == BLACK) {
        sibbling->color = RED;

        node = node->parent;
      } else {
        if (sibbling->right->color == BLACK) {
          sibbling->left->color = BLACK;
          sibbling->color = RED;

          rightRotate(tree, sibbling);

          sibbling = node->parent->right;
        }

        sibbling->color = node->parent->color;
        node->parent->color = BLACK;
        sibbling->right->color = BLACK;

        leftRotate(tree, node->parent);

        node = tree->root;
      }
    } else {
      sibbling = node->parent->left;

      if (sibbling->color == RED) {
        sibbling->color = BLACK;
        node->parent->color = RED;

        rightRotate(tree, node->parent);

        sibbling = node->parent->left;
      }

      if (sibbling->right->color == BLACK && sibbling->left->color == BLACK) {
        sibbling->color = RED;

        node = node->parent;
      } else {
        if (sibbling->left->color == BLACK) {
          sibbling->right->color = BLACK;
          sibbling->color = RED;

          leftRotate(tree, sibbling);

          sibbling = node->parent->left;
        }

        sibbling->color = node->parent->color;
        node->parent->color = BLACK;
        sibbling->left->color = BLACK;

        rightRotate(tree, node->parent);

        node = tree->root;
      }
    }
  }

  node->color = BLACK;
}*/

Node *sibbling(Node *node) {
  return node == node->parent->left ? node->parent->right : node->parent->left;
}

//funcao modificada
void deleteFixup(Tree *tree, Node *x) {
  while (x != tree->root && x->color == BLACK) {
    Node *sib = sibbling(x);

    if (x == x->parent->left) {
      if (sib->color == RED) {
        sib->color = BLACK;
        x->parent->color = RED;
        leftRotate(tree, x->parent);
        sib = sibbling(x);
      }

      if (sib->right->color == BLACK && sib->left->color == BLACK) {
        sib->color = RED;
        x = x->parent;
      } else {
        if (sib->right->color == BLACK) {
          sib->left->color = BLACK;
          sib->color = RED;
          rightRotate(tree, sib);
          sib = sibbling(x);
        }

        sib->color = x->parent->color;
        x->parent->color = BLACK;
        sib->right->color = BLACK;
        leftRotate(tree, x->parent);
        x = tree->root;
      }
  } else {
      if (sib->color == RED) {
        sib->color = BLACK;
        x->parent->color = RED;
        rightRotate(tree, x->parent);
        sib = sibbling(x);
      }

      if (sib->left->color == BLACK && sib->right->color == BLACK) {
        sib->color = RED;
        x = x->parent;
      } else {
        if (sib->left->color == BLACK) {
          sib->right->color = BLACK;
          sib->color = RED;
          leftRotate(tree, sib);
          sib = sibbling(x);
        }

        sib->color = x->parent->color;
        x->parent->color = BLACK;
        sib->left->color = BLACK;
        rightRotate(tree, x->parent);
        x = tree->root;
      }
    }
  }

  x->color = BLACK;
}

void delete(Tree *tree, int key) {
  Node *node = search(tree->root, key);
  if (equals(node, &EXTERNAL_NODE)) return;

  Node *pointerY = node, *pointerX;
  int pointerYOriginalColor = pointerY->color;

  if (node->left == &EXTERNAL_NODE) {
    pointerX = node->right;

    moveParent(tree, node, node->right);
  } else {
    if (node->right == &EXTERNAL_NODE) {
      pointerX = node->left;

      moveParent(tree, node, node->left);
    } else {
      pointerY = minimum(node->right);

      pointerYOriginalColor = pointerY->color;
      pointerX = pointerY->right;

      if (pointerY->parent == node) {
        pointerX->parent = pointerY;
      } else {
        moveParent(tree, pointerY, pointerY->right);

        pointerY->right = node->right;
        pointerY->right->parent = pointerY;
      }

      moveParent(tree, node, pointerY);

      pointerY->left = node->left;
      pointerY->left->parent = pointerY;
      pointerY->color = node->color;
    }
  }

  free(node);

  if (pointerYOriginalColor == BLACK) {
    deleteFixup(tree, pointerX);
  }
}

int verifyNode(Node *root) {
  int verifyLeft, verifyRight;

  if (root == &EXTERNAL_NODE) return true;
  if (root->color == RED) {
    if (root->right->color == BLACK && root->left->color == BLACK) {
      verifyRight = verifyNode(root->right);
      verifyLeft = verifyNode(root->left);
      return verifyRight && verifyLeft;
    }

    return false;
  } else {
    verifyRight = verifyNode(root->right);
    verifyLeft = verifyNode(root->left);

    return verifyRight && verifyLeft;
  }
}

int blackHeight(Node *root) {
  if (root == &EXTERNAL_NODE) return 1;

  int leftHeight = blackHeight(root->left);
  int rightHeight = blackHeight(root->right);

  if (leftHeight != rightHeight) return -1;

  if (root->color == BLACK) {
    return 1 + (rightHeight > leftHeight ? rightHeight : leftHeight);
  } else {
    return rightHeight > leftHeight ? rightHeight : leftHeight;
  }
}

int isRedBlackTree(Node *root) {
  Node *auxiliary = root;
  if (auxiliary->color == RED) return false;

  int verifyLeft = verifyNode(auxiliary->left);
  int verifyRight = verifyNode(auxiliary->right);
  int leftHeight = blackHeight(auxiliary->left);
  int rightHeight = blackHeight(auxiliary->right);

  if ((leftHeight != rightHeight) || (rightHeight == -1) || (leftHeight == -1)) {
    return false;
  }

  return verifyLeft && verifyRight;
}

void printTree(Node *root) {
  if (root != NULL && !equals(root, &EXTERNAL_NODE)) {
    printTree(root->left);
    printf("%d - %s\n", root->key, root->color == RED ? "Rubro" : "Negro");
    printTree(root->right);
  }
}

void treeReport(Tree *tree, int treeIndex) {
  if (tree == NULL || equals(tree->root, &EXTERNAL_NODE)) return;

  printf("----------Árvore %d-------------\n", treeIndex);

  printf("Arvore %s\n", isRedBlackTree(tree->root) ? "é Rubro-Negra" : "não é Rubro-Negra");

  printf("Altura Negra: %d\n", blackHeight(tree->root));

  printf("Árvore:\n");
  printTree(tree->root);

  printf("\n");
}