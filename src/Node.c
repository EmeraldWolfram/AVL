#include "Node.h"
#include <stdlib.h>

Node* createNode(int thisData, int thisBF){
  Node* newNode   = malloc(sizeof(Node));
  newNode->left   = NULL;
  newNode->right  = NULL;
  newNode->balanceFactor = thisBF;
  newNode->data   = thisData;
  
  return newNode;
}

Node* linkNode(Node* root, Node* thisLeft, Node* thisRight){
  if(thisRight != NULL){
    root->right = thisRight;
    // root->balanceFactor++;
  }
  if(thisLeft != NULL){
    root->left  = thisLeft;
    // root->balanceFactor--;
  }
  
  return root;
}