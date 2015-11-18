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
      if((*rootPtr)->right != NULL){
        newRoot = avlGetReplacer(&(*rootPtr)->right, &childChange);
        brokenLeft = (*rootPtr)->left;
        if((*rootPtr)->right->left != NULL)
          brokenRight = (*rootPtr)->right;
        else
          brokenRight = NULL;
        newRoot->balanceFactor = currentBF;
        if(childChange == 1)
          newRoot->balanceFactor--;
        if(newRoot->balanceFactor < 1)
          *heightChange = 1;
      }
      else{
        newRoot = (*rootPtr)->left;
        brokenLeft  = NULL;
        brokenRight = NULL;
        newRoot->balanceFactor = currentBF;
        newRoot->balanceFactor++;
        *heightChange = 1;
      }
      (*rootPtr)        = newRoot;
      (*rootPtr)->right = brokenRight;
      (*rootPtr)->left  = brokenLeft;
      
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
          *heightChange = 1;
          leftRightRotate(rootPtr);
        }
        else{
          (*rootPtr)->balanceFactor++;
          (*rootPtr)->left->balanceFactor++; 
          if((*rootPtr)->left->balanceFactor == 0)
            (*rootPtr)->balanceFactor++;
          if((*rootPtr)->left->balanceFactor != 0)
            *heightChange = 0;
          rightRotate(rootPtr);    
        } 
      }
    
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

Node* avlGetReplacer(Node** rootPtr, int* heightChange){
  Node* replacerNode, *brokenLeft, *brokenRight;
  int childChange;
  *heightChange = 1;
  
  if((*rootPtr) == NULL)
    ThrowError(ERR_NULL_PTR, "Input AVL is Empty");
  
  if((*rootPtr)->left == NULL){
    replacerNode  = (*rootPtr);
  }
  else{
    brokenRight = (*rootPtr)->left->right;
    if((*rootPtr)->left != NULL){
      replacerNode = avlGetReplacer(&(*rootPtr)->left, &childChange);
      if(replacerNode == (*rootPtr)->left){
        (*rootPtr)->left = brokenRight;
        if((*rootPtr)->balanceFactor >= 0)
          *heightChange = 0;
      }
    }
    if(childChange == 1)
      (*rootPtr)->balanceFactor++;
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
  
  replacerNode->right = NULL;
  return replacerNode;
}





