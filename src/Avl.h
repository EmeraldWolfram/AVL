#ifndef Avl_H
#define Avl_H
#include "Node.h"
#include "ErrorObject.h"

int avlAdd(Node** rootPtr, Node* newNode);
Node* avlRemove(Node** rootPtr, int value, int* heightChange);


#endif // Avl_H
