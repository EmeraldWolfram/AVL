#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  int data;
  int balanceFactor;
  Node *left;
  Node *right;
};

Node* createNode(int thisData, int thisBF);
Node* linkNode(Node* root, Node* left, Node* right);


#endif // Node_H
