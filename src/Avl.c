#include "Avl.h"
#include "Rotation.h"
#include <stdlib.h>

int avlAdd(Node** rootPtr, Node* newNode){
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
  //*********** ROTATION ***************************
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

Node* avlRemove(Node** rootPtr, int value, int* heightChange){
  Node* removedNode = NULL;
  //*************************************
  int childChange;
  *heightChange = 0;
  //*************************************
  int currentBF   = (*rootPtr)->balanceFactor;
  Node *tempNode, *newRoot;
  
  if(*rootPtr == NULL)
    ThrowError(ERR_NULL_PTR, "Input AVL is Empty");
  
  if(value == (*rootPtr)->data){
    removedNode = (*rootPtr);
    if((*rootPtr)->left == NULL && (*rootPtr)->right == NULL){
      (*rootPtr) = NULL;
      *heightChange = 1;
    }
    else{
      Node *brokenLeft, *brokenRight;
      if((*rootPtr)->left != NULL){
        tempNode   = (*rootPtr);
        newRoot    = (*rootPtr)->left;
        brokenLeft = (*rootPtr)->left->left;
        brokenRight = (*rootPtr)->right;
        while(newRoot->right != NULL){
          tempNode = newRoot;
          newRoot  = newRoot->right;
        }
        newRoot->balanceFactor = currentBF;
        if((*rootPtr)->left->right != NULL){
          tempNode->balanceFactor--;
          tempNode->right   = NULL;
          brokenLeft        = (*rootPtr)->left;
        }
        if(tempNode->left == NULL || newRoot == (*rootPtr)->left)
          newRoot->balanceFactor++;
      }
      else{
        tempNode    = (*rootPtr);
        newRoot     = (*rootPtr)->right;
        brokenRight = (*rootPtr)->right->right;
        brokenLeft  = (*rootPtr)->left;
        while(newRoot->left != NULL){
          tempNode = newRoot;
          newRoot  = newRoot->left;
        }
        newRoot->balanceFactor = currentBF;
        if((*rootPtr)->right->left != NULL){
          tempNode->balanceFactor++;
          tempNode->left   = NULL;
          brokenRight      = (*rootPtr)->right;
        }
        if(tempNode->right == NULL || newRoot == (*rootPtr)->right)
          newRoot->balanceFactor--;
      }
      if(newRoot->balanceFactor == 0)
        *heightChange = 1;
      (*rootPtr)        = newRoot;
      (*rootPtr)->right = brokenRight;
      (*rootPtr)->left  = brokenLeft;
    }
    return removedNode;
  }
  else if(value > (*rootPtr)->data){
    if((*rootPtr)->right == NULL)
      return NULL;
    removedNode = avlRemove(&((*rootPtr)->right), value, &childChange);
    if(childChange == 1)
      (*rootPtr)->balanceFactor--;
    if((*rootPtr)->balanceFactor == 0)
      *heightChange = 1;
  }
  else{
    if((*rootPtr)->left == NULL)
      return NULL;
    removedNode = avlRemove(&((*rootPtr)->left), value, &childChange);
    if(childChange == 1)
      (*rootPtr)->balanceFactor++;
    if((*rootPtr)->balanceFactor == 0)
      *heightChange = 1;
  }
  //*********** ROTATION ***************************
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
  return removedNode;
}






