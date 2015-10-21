#include "customAssertion.h"
#include "unity.h"
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

void customTestAssertNode(int expectedData, int expectedBalanceFactor, Node* actualNode, int lineNumber){

  if(actualNode == NULL){
    CUSTOM_TEST_FAIL(lineNumber, "Expected Not NULL");
  }
  else{
    if(actualNode->data != expectedData){
      CUSTOM_TEST_FAIL(lineNumber,"Expected data to be %d was %d", expectedData, actualNode->data);
    }
    if(actualNode->balanceFactor != expectedBalanceFactor){
      CUSTOM_TEST_FAIL(lineNumber,"Expected balance factor to be %d was %d", expectedBalanceFactor, actualNode->balanceFactor);
    }
  }
}

void customTestAssertTreeLink(Node* expectNode, Node* expectLeft, Node* expectRight, Node* actualNode, int lineNumber){

  if(actualNode == NULL){
    CUSTOM_TEST_FAIL(lineNumber, "Expected Actual Node Not NULL");
  }
  
  if(actualNode != expectNode){
    CUSTOM_TEST_FAIL(lineNumber,"Expected root as %X was %X", expectNode, actualNode);
  }
    
  if(expectLeft == NULL){
    if(actualNode->left != NULL){
      CUSTOM_TEST_FAIL(lineNumber,"Expected left node to be NULL");
    }
  }
  else{
    if(actualNode->left == NULL){
      CUSTOM_TEST_FAIL(lineNumber, "Expected left node not NULL");
    }
    else if((actualNode->left) != (expectLeft)){
      CUSTOM_TEST_FAIL(lineNumber,"Expected left Node point to %X but pointed to %X", expectLeft, actualNode->left);
    }
  }
    
  if(expectRight == NULL){
    if(actualNode->right != NULL){
      CUSTOM_TEST_FAIL(lineNumber,"Expected right node to be NULL");
    }
  }
  else{
    if(actualNode->right == NULL){
      CUSTOM_TEST_FAIL(lineNumber, "Expected right node not NULL");
    }
    else if((actualNode->right->data) != (expectRight->data)){
      CUSTOM_TEST_FAIL(lineNumber,"Expected right Node point to %X but pointed to %X", expectRight, actualNode->right);
    }
  }
}
