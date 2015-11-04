#include "Rotation.h"
#include <stdlib.h>
#include <stdio.h>

void rightRotate(Node** tree){
  Node* brokenNode = (*tree)->left->right;
  Node* rightNode = (*tree);
  
  *tree = (*tree)->left;
  (*tree)->right = rightNode;
  (*tree)->right->left = brokenNode;
}

void leftRotate(Node** tree){
  Node* brokenNode = (*tree)->right->left;
  Node* leftNode = (*tree);
  
  *tree = (*tree)->right;
  (*tree)->left = leftNode;
  (*tree)->left->right = brokenNode;
}

void rightLeftRotate(Node** tree){
  Node* brokenLeft = (*tree)->right->left->left;
  Node* brokenRight = (*tree)->right->left->right;
  Node* leftNode  = *tree;
  Node* rightNode = (*tree)->right;
  
  *tree = (*tree)->right->left;
  (*tree)->left   = leftNode;
  (*tree)->right  = rightNode;
  (*tree)->left->right = brokenLeft;
  (*tree)->right->left = brokenRight;
}

void leftRightRotate(Node** tree){
  Node* brokenLeft = (*tree)->left->right->left;
  Node* brokenRight = (*tree)->left->right->right;
  Node* rightNode  = *tree;
  Node* leftNode = (*tree)->left;
  
  *tree = (*tree)->left->right;
  (*tree)->left   = leftNode;
  (*tree)->right  = rightNode;
  (*tree)->left->right = brokenLeft;
  (*tree)->right->left = brokenRight;
}