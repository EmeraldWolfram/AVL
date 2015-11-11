#include "unity.h"
#include "Avl.h"
#include "Rotation.h"
#include "customAssertion.h"
#include "ErrorObject.h"
#include "Node.h"

Node  node10, node20, node30, node40, node50, node60, node70, node80, node90;
Node  node100, node110, node120, node130, node140, node150, node160, node170;
Node  node180, node190;

//TEST_ASSERT_TREE_LINK(Node* expectNode, Node* expectLeft, Node* expectRight, Node* actualNode)
//This custom assertion use to test the addresses of the Node to be tested including the left and right node

//TEST_ASSERT_EQUAL_NODE(expectedData, expectedBalanceFactor, actualNode);
//This custom assertion use to test all the data within the Node to be tested

void resetNode(Node* node, int value){
  node->data = value;
  node->balanceFactor = 0;
  node->left = NULL;
  node->right = NULL;
}

void setUp(void){
  resetNode(&node10, 10);
  resetNode(&node20, 20);
  resetNode(&node30, 30);
  resetNode(&node40, 40);
  resetNode(&node50, 50);
  resetNode(&node60, 60);
  resetNode(&node70, 70);
  resetNode(&node80, 80);
  resetNode(&node90, 90);
  resetNode(&node100, 100);
  resetNode(&node110, 110);
  resetNode(&node120, 120);
  resetNode(&node130, 130);
  resetNode(&node140, 140);
  resetNode(&node150, 150);
  resetNode(&node160, 160);
  resetNode(&node170, 170);
  resetNode(&node180, 180);
  resetNode(&node190, 190);
}

void tearDown(void){}

/**
 *  
 *     (60)0    (-90)       (60)-1
 *    /    \    ----->      /
 *  (30)0 (90)0          (30)0
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_90_should_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node90);
  
  Node* removedNode = avlRemove(&testTree, 90, 0);
  
  TEST_ASSERT_EQUAL_PTR(&node90, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, &node30, NULL, testTree);
  TEST_ASSERT_EQUAL_NODE(30,  0, &node30);
  TEST_ASSERT_EQUAL_NODE(60, -1, &node60);
}

/**
 *  
 *     (60)0    (-30)       (60)+1
 *    /    \    ----->        \
 *  (30)0 (90)0               (90)0
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_30_should_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node90);
  
  Node* removedNode = avlRemove(&testTree, 30, 0);
  
  TEST_ASSERT_EQUAL_PTR(&node30, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, NULL, &node90, testTree);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
  TEST_ASSERT_EQUAL_NODE(60,  1, &node60);
}


/**
 *  
 *        (60)0       -(20)        (60)0
 *       /    \       ----->      /    \
 *   (20)0    (90)-1           (10)+1   (90)-1
 *  /   \     /                   \     /
 *(10)0(40)0(70)0                (40)0(70)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_20_should_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node10);
  i = avlAdd(&testTree, &node70);
  i = avlAdd(&testTree, &node40);
  
  Node* removedNode = avlRemove(&testTree, 20, 0);
  
  TEST_ASSERT_EQUAL_PTR(&node20, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, &node10, &node90, testTree);
  TEST_ASSERT_TREE_LINK(&node10,    NULL, &node40, testTree->left);
  TEST_ASSERT_TREE_LINK(&node90, &node70,    NULL, testTree->right);
  TEST_ASSERT_EQUAL_NODE(10,  1, &node10);
  TEST_ASSERT_EQUAL_NODE(90, -1, &node90);
  TEST_ASSERT_EQUAL_NODE(70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(40,  0, &node40);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
}






