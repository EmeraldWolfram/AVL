#ifndef Avl_H
#define Avl_H
#include "Node.h"
#include "ErrorObject.h"

int avlAdd(Node** rootPtr, Node* newNode);
Node* avlRemove(Node** rootPtr, int value, int* heightChange);
Node* avlGetReplacer(Node** rootPtr, int* heightChange);


void testPtr(int* ptr);


#endif // Avl_H
