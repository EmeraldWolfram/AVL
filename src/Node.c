#include "Node.h"
#include <stdlib.h>

Node* createNode(int thisData){
  Node* newNode   = malloc(sizeof(Node));
  newNode->left   = NULL;
  newNode->right  = NULL;
  newNode->balanceFactor = 0;
  newNode->data   = thisData;
  
  return newNode;
}

Node* linkNode(Node* root, Node* thisLeft, Node* thisRight){
  if(thisRight != NULL){
    root->right = thisRight;
    root->balanceFactor++;
  }
  if(thisLeft != NULL){
    root->left  = thisLeft;
    root->balanceFactor--;
  }
  
  return root;
}

Node* initializeTreeForLeftTest(){
  Node* root0 = linkNode(createNode(90), NULL, createNode(100));
	Node* root1 = linkNode(createNode(80), createNode(70), root0);
	Node* root2 = linkNode(createNode(150), createNode(130), NULL);
	Node* root3 = linkNode(createNode(110), root1, root2);
	Node* root4 = linkNode(createNode(30), createNode(20), NULL);
	Node* root5 = linkNode(createNode(60), root4, root3);
  
  return root5;
}

Node* initializeTreeForRightTest(){
  Node* root0 = linkNode(createNode(15), createNode(10), NULL);
	Node* root1 = linkNode(createNode(45), createNode(36), createNode(50));
	Node* root2 = linkNode(createNode(30), root0, root1);
	Node* root3 = linkNode(createNode(90), createNode(75), createNode(115));
	Node* root5 = linkNode(createNode(60), root2, root3);
  
  return root5;
}