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
  int localChange = 1;
  int currentBF   = (*rootPtr)->balanceFactor;
  heightChange = &localChange;
  Node *tempNode, *newRoot;
  
  if(*rootPtr == NULL)
    ThrowError(ERR_NULL_PTR, "Input AVL is Empty");
  
  if(value == (*rootPtr)->data){
    removedNode = (*rootPtr);
    if((*rootPtr)->left == NULL && (*rootPtr)->right == NULL)
      (*rootPtr) = NULL;
    // else{
      // Node *brokenLeft, *brokenRight;
      // if((*rootPtr)->left != NULL && (*rootPtr)->right != NULL){
        // localChange = 0;
      // }
      // if((*rootPtr)->left != NULL){
        // newRoot    = (*rootPtr)->left;
        // brokenLeft = (*rootPtr)->left->left;
        // brokenRight = (*rootPtr)->right;
        // while(newRoot->right != NULL){
          // tempNode = newRoot;
          // newRoot  = newRoot->right;
        // }
        // if((*rootPtr)->left->right != NULL){
          // tempNode->balanceFactor--;
          // if(tempNode->left == NULL)
            // (*rootPtr)->left->balanceFactor--;
          // else
            // localChange = 0;
          // tempNode->right   = NULL;
          // brokenLeft        = (*rootPtr)->left;
        // }
        // newRoot->balanceFactor = currentBF;
        // if(localChange == 0)
          // newRoot->balanceFactor++;
      // }
      // else{
        // newRoot     = (*rootPtr)->right;
        // brokenRight = (*rootPtr)->right->right;
        // brokenLeft  = (*rootPtr)->left;
        // while(newRoot->left != NULL){
          // tempNode = newRoot;
          // newRoot  = newRoot->left;
        // }
        // if((*rootPtr)->right->left != NULL){
          // tempNode->balanceFactor++;
          // if(tempNode->right == NULL)
            // (*rootPtr)->right->balanceFactor++;
          // else
            // localChange = 0;
          // tempNode->left   = NULL;
          // brokenRight        = (*rootPtr)->right;
        // }
        // newRoot->balanceFactor = currentBF;
        // if(localChange == 1)
          // newRoot->balanceFactor--;
      // }
      // (*rootPtr)        = newRoot;
      // (*rootPtr)->right = brokenRight;
      // (*rootPtr)->left  = brokenLeft;
    // }
    return removedNode;
  }
  else if(value > (*rootPtr)->data){
    if((*rootPtr)->right == NULL)
      return NULL;
    removedNode = avlRemove(&((*rootPtr)->right), value, heightChange);
    // if(heightChange != 0)
    (*rootPtr)->balanceFactor--;
    if((*rootPtr)->balanceFactor == 0)
      localChange = 0;
  }
  else{
    if((*rootPtr)->left == NULL)
      return NULL;
    removedNode = avlRemove(&((*rootPtr)->left), value, heightChange);
    // if(*heightChange == 1){
    (*rootPtr)->balanceFactor++;
    // }
    if((*rootPtr)->balanceFactor == 0)
      localChange = 0;
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









