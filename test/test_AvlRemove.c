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
  
  Node* removedNode = avlRemove(&testTree, 90, &i);
  
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
  
  Node* removedNode = avlRemove(&testTree, 30, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node30, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, NULL, &node90, testTree);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
  TEST_ASSERT_EQUAL_NODE(60,  1, &node60);
}

/**
 *  
 *        (60)0       -(20)        (70)0
 *       /    \       ----->      /    \
 *   (20)0    (90)-1           (60)0   (90)0
 *            /      
 *          (70)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_20_should_call_rightLeftRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node70);
  
  Node* removedNode = avlRemove(&testTree, 20, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node20, removedNode);
  TEST_ASSERT_TREE_LINK(&node70, &node60, &node90, testTree);
  TEST_ASSERT_EQUAL_NODE(70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
}

/**
 *  
 *        (60)0       -(40)        (90)-1
 *       /    \       ----->      /    \
 *   (40)0    (90)0            (60)+1  (100)0
 *            /  \                \
 *          (70)0(100)0          (70)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_40_should_call_leftRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node70);
  i = avlAdd(&testTree, &node100);
  
  Node* removedNode = avlRemove(&testTree, 40, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node40, removedNode);
  TEST_ASSERT_TREE_LINK(&node90, &node60, &node100, testTree);
  TEST_ASSERT_TREE_LINK(&node60,    NULL,  &node70, testTree->left);
  TEST_ASSERT_EQUAL_NODE(70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(90, -1, &node90);
  TEST_ASSERT_EQUAL_NODE(100, 0, &node100);
  TEST_ASSERT_EQUAL_NODE(60,  1, &node60);
}

/**
 *  
 *        (60)0       -(30)        (90)0
 *       /    \       ----->      /    \
 *   (30)0    (90)0            (60)0  (100)0
 *               \                
 *              (100)0          
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_30_should_call_leftRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node100);
  
  Node* removedNode = avlRemove(&testTree, 30, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node30, removedNode);
  TEST_ASSERT_TREE_LINK(&node90, &node60, &node100, testTree);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
  TEST_ASSERT_EQUAL_NODE(100, 0, &node100);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
}

/**
 *  
 *        (60)0       -(90)        (40)0
 *       /    \       ----->      /    \
 *   (20)+1   (90)0            (20)0   (60)0
 *      \      
 *      (40)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_90_should_call_leftRightRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node40);
  
  Node* removedNode = avlRemove(&testTree, 90, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node90, removedNode);
  TEST_ASSERT_TREE_LINK(&node40, &node20, &node60, testTree);
  TEST_ASSERT_EQUAL_NODE(20,  0, &node20);
  TEST_ASSERT_EQUAL_NODE(40,  0, &node40);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
}

/**
 *  
 *        (60)-1       -(90)        (40)+1
 *       /    \       ----->       /    \
 *   (40)0    (90)0             (20)0   (60)-1
 *   /  \                               /
 *(20)0 (50)0                        (50)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_90_should_call_rightRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node50);
  
  Node* removedNode = avlRemove(&testTree, 90, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node90, removedNode);
  TEST_ASSERT_TREE_LINK(&node40, &node20, &node60, testTree);
  TEST_ASSERT_TREE_LINK(&node60, &node50,    NULL, testTree->right);
  TEST_ASSERT_EQUAL_NODE(40,  1, &node40);
  TEST_ASSERT_EQUAL_NODE(20,  0, &node20);
  TEST_ASSERT_EQUAL_NODE(50,  0, &node50);
  TEST_ASSERT_EQUAL_NODE(60, -1, &node60);
}

/**
 *  
 *        (60)0       -(80)        (30)0
 *       /    \       ----->      /    \
 *   (30)0    (80)0            (20)0  (60)0
 *    /                
 * (20)0          
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_80_should_call_rightRotate_and_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node80);
  i = avlAdd(&testTree, &node20);
  
  Node* removedNode = avlRemove(&testTree, 80, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node80, removedNode);
  TEST_ASSERT_TREE_LINK(&node30, &node20, &node60, testTree);
  TEST_ASSERT_EQUAL_NODE(30,  0, &node30);
  TEST_ASSERT_EQUAL_NODE(20,  0, &node20);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
}

/**
 *  
 *        (60)0       -(20)        (60)+1
 *       /    \       ----->      /    \
 *   (20)0    (90)-1           (10)0   (90)-1
 *  /         /                        /
 *(10)0    (70)0                    (70)0
 *
 *
 *********************************************************/

void test_avlRemove_given_treeA_remove_20_should_become_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node10);
  i = avlAdd(&testTree, &node70);

  Node* removedNode = avlRemove(&testTree, 20, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node20, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, &node10, &node90, testTree);
  TEST_ASSERT_TREE_LINK(&node90, &node70,    NULL, testTree->right);
  TEST_ASSERT_EQUAL_NODE(10,  0, &node10);
  TEST_ASSERT_EQUAL_NODE(90, -1, &node90);
  TEST_ASSERT_EQUAL_NODE(70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(60,  1, &node60);
}

/**
 *  
 *         (60)0       -(30)          (60)+1
 *        /     \       ----->       /     \
 *    (30)-1    (80)+1           (20)0     (80)+1
 *   /    \     /  \            /   \     /    \
 *(10)+1 (40)0(70)0(100)-1  (10)0 (40)0 (70)0(100)-1
 *   \              /                         /
 *   (20)0        (90)0                     (90)0
 *********************************************************/

void test_avlRemove_given_treeA_remove_30_should_turn_to_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node80);
  i = avlAdd(&testTree, &node10);
  i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node70);
  i = avlAdd(&testTree, &node100);
  i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node90);

  Node* removedNode = avlRemove(&testTree, 30, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node30, removedNode);
  TEST_ASSERT_TREE_LINK(&node60, &node20, &node80, testTree);
  TEST_ASSERT_TREE_LINK(&node20, &node10, &node40, testTree->left);
  TEST_ASSERT_TREE_LINK(&node80, &node70, &node100, testTree->right);
  TEST_ASSERT_TREE_LINK(&node100, &node90,    NULL, testTree->right->right);
  TEST_ASSERT_EQUAL_NODE(60,  1, &node60);
  TEST_ASSERT_EQUAL_NODE(20,  0, &node20);
  TEST_ASSERT_EQUAL_NODE(80,  1, &node80);
  TEST_ASSERT_EQUAL_NODE(10,  0, &node10);
  TEST_ASSERT_EQUAL_NODE(40,  0, &node40);
  TEST_ASSERT_EQUAL_NODE(70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(100,-1, &node100);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
}

/**
 *  
 *            (80)-1        -(40)            (80)-1
 *           /     \       ------>          /     \
 *       (40)-1    (120)0              (30)-1    (120)0
 *       /  \      /   \               /   \     /    \
 *    (20)0(60)0(110)0(140)0      (20)-1 (60)0(110)0 (140)0
 *    /   \                       /
 * (10)0 (30)0                 (10)0
 *  
 *  
 *  
 *********************************************************/

void test_avlRemove_given_treeA_remove_40_should_turn_to_treeB(void){
  Node* testTree = &node80;
  int i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node120);
  i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node60);
  i = avlAdd(&testTree, &node110);
  i = avlAdd(&testTree, &node140);
  i = avlAdd(&testTree, &node10);
  i = avlAdd(&testTree, &node30);

  Node* removedNode = avlRemove(&testTree, 40, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node40, removedNode);
  TEST_ASSERT_TREE_LINK(&node80, &node30, &node120, testTree);
  TEST_ASSERT_TREE_LINK(&node30, &node20,  &node60, testTree->left);
  TEST_ASSERT_TREE_LINK(&node20, &node10,     NULL, testTree->left->left);
  TEST_ASSERT_TREE_LINK(&node120,&node110,&node140, testTree->right);
  TEST_ASSERT_EQUAL_NODE( 80, -1, &node80);
  TEST_ASSERT_EQUAL_NODE( 30, -1, &node30);
  TEST_ASSERT_EQUAL_NODE(120,  0, &node120);
  TEST_ASSERT_EQUAL_NODE( 20, -1, &node20);
  TEST_ASSERT_EQUAL_NODE( 60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE(110,  0, &node110);
  TEST_ASSERT_EQUAL_NODE(140,  0, &node140);
  TEST_ASSERT_EQUAL_NODE( 10,  0, &node10);
}

/**
 *  
 *            -1(80)        -(60)            (80)0
 *           /     \       ------>          /     \
 *     -1(60)      (120)0              0(30)     (120)0
 *       /  \      /   \               /   \     /    \
 *  -1(30) 0(70)(110)0(140)0       0(10) 0(70)(110)0 (140)0
 *    / 
 *0(10)
 *  
 *  
 *  
 *********************************************************/

void test_avlRemove_given_treeA_remove_60_should_turn_to_treeB(void){
  Node* testTree = &node80;
  int i = avlAdd(&testTree, &node60);
  i = avlAdd(&testTree, &node120);
  i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node70);
  i = avlAdd(&testTree, &node110);
  i = avlAdd(&testTree, &node140);
  i = avlAdd(&testTree, &node10);

  Node* removedNode = avlRemove(&testTree, 60, &i);
  
  TEST_ASSERT_EQUAL_PTR(&node60, removedNode);
  TEST_ASSERT_TREE_LINK(&node80, &node30, &node120, testTree);
  TEST_ASSERT_TREE_LINK(&node30, &node10,  &node70, testTree->left);
  TEST_ASSERT_TREE_LINK(&node120,&node110,&node140, testTree->right);
  TEST_ASSERT_EQUAL_NODE( 80,  0, &node80);
  TEST_ASSERT_EQUAL_NODE( 30,  0, &node30);
  TEST_ASSERT_EQUAL_NODE(120,  0, &node120);
  TEST_ASSERT_EQUAL_NODE( 10,  0, &node10);
  TEST_ASSERT_EQUAL_NODE( 70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(110,  0, &node110);
  TEST_ASSERT_EQUAL_NODE(140,  0, &node140);
}