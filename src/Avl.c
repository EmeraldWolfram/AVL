#include "Avl.h"
#include <stdlib.h>

int avlAdd(Node** rootPtr, Node* newNode){
  int currentBalance = (*rootPtr)->balanceFactor;
  int newBalance = 0;
  if(newNode == NULL)
    return 0;
  
  if(((*rootPtr)->data) > (newNode->data)){
    if((*rootPtr)->left == NULL){
      (*rootPtr)->left = newNode;
      currentBalance--;
    }
    else{
      newBalance = avlAdd(&(*rootPtr)->left, newNode);
      if(newBalance != 0)
        currentBalance--;
    }
  }
  else{
    if((*rootPtr)->right == NULL){
      (*rootPtr)->right = newNode;
      currentBalance++;
    }
    else{
      newBalance = avlAdd(&(*rootPtr)->right, newNode);
      if(newBalance != 0)
        currentBalance++;      
    }
  }

  (*rootPtr)->balanceFactor = currentBalance;
  
  if(currentBalance == 0)
    return 0;
  else
    return 1;
}