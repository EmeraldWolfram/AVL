#include "Avl.h"
#include <stdlib.h>

int avlAdd(Node** rootPtr, Node* newNode){
  // int currentBalance = (*rootPtr)->balanceFactor;
  int newBalance = 1;
  if(newNode == NULL)
    return 0;
  
  if(((*rootPtr)->data) > (newNode->data)){
    if((*rootPtr)->left == NULL){
      (*rootPtr)->left = newNode;
      (*rootPtr)->balanceFactor--;
    }
    else{
      newBalance = avlAdd(&(*rootPtr)->left, newNode);
      if(newBalance != 0)
        (*rootPtr)->balanceFactor--;
    }
  }
  else{
    if((*rootPtr)->right == NULL){
      (*rootPtr)->right = newNode;
      (*rootPtr)->balanceFactor++;
    }
    else{
      newBalance = avlAdd(&(*rootPtr)->right, newNode);
      if(newBalance != 0)
        (*rootPtr)->balanceFactor++;      
    }
  }

  if((*rootPtr)->balanceFactor == 0 || newBalance == 0)
    return 0;
  else
    return 1;
}