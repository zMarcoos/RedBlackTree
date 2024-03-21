#include <stdio.h>
#include <stdlib.h>
#include "treeRedBlack.h"

int main() {
  int treeAmount = 1,
    nodeAmount = 20;

  Tree *currentTree = startTree();

  printf("Inserindo...\n");
  
  for (int nodeIndex = 0; nodeIndex < nodeAmount; nodeIndex++) {
    insert(currentTree, nodeIndex);
  }

  treeReport(currentTree, 0);

  printf("Removendo...\n");
  
  /*
  for (int nodeIndex = 0; nodeIndex < nodeAmount; nodeIndex++) {
    delete(currentTree, nodeIndex);
  }*/
  
  delete(currentTree, 7);

  treeReport(currentTree, 0);

  free(currentTree);

  return 0;
}