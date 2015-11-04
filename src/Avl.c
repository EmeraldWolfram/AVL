#include "Avl.h"
#include "Rotation.h"
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
  if((*rootPtr)->balanceFactor == 2){
    if((*rootPtr)->right->balanceFactor == -1){
      (*rootPtr)->balanceFactor = 0;
      (*rootPtr)->right->balanceFactor = 0;
      if((*rootPtr)->right->left->balanceFactor == -1){
        (*rootPtr)->right->balanceFactor = 1;   
      }
      if((*rootPtr)->right->left->balanceFactor == 1){
        (*rootPtr)->balanceFactor = -1;
      }
      (*rootPtr)->right->left->balanceFactor = 0;   
      rightLeftRotate(rootPtr);
    }
    else{
      (*rootPtr)->right->balanceFactor--;  
      (*rootPtr)->balanceFactor--;
      if((*rootPtr)->right->balanceFactor == 0)
        (*rootPtr)->balanceFactor--;
      leftRotate(rootPtr);
    }
  }
  if((*rootPtr)->balanceFactor == -2){
    if((*rootPtr)->left->balanceFactor == 1){
      (*rootPtr)->balanceFactor = 0;
      (*rootPtr)->left->balanceFactor = 0;
      if((*rootPtr)->left->right->balanceFactor == 1){
        (*rootPtr)->left->balanceFactor = -1;   
      }
      if((*rootPtr)->left->right->balanceFactor == -1){
        (*rootPtr)->balanceFactor = 1;
      }
      (*rootPtr)->left->right->balanceFactor = 0;   
      leftRightRotate(rootPtr);
    }
    else{
      (*rootPtr)->balanceFactor++;
      (*rootPtr)->left->balanceFactor++; 
      if((*rootPtr)->left->balanceFactor == 0)
        (*rootPtr)->balanceFactor++;
      rightRotate(rootPtr);    
    }
  }
  
  if((*rootPtr)->balanceFactor == 0 || newBalance == 0)
    return 0;
  else
    return 1;    
  

}