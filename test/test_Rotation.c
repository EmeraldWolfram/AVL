#include "unity.h"
#include "Rotation.h"
#include "Avl.h"
#include "Node.h"
#include "customAssertion.h"
#include "ErrorObject.h"
#include <stdlib.h>
#include <stdio.h>

Node  node10, node20, node30, node40, node50, node60, node70, node80, node90;
Node  node100, node110, node120, node130, node140, node150, node160, node170;

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
}

void tearDown(void){}

/**
 *  Left Rotate should rotate the tree from tree A to tree B as shown below
 *
 *  Tree A                                          Tree B
 *  
 *            (60)                                    (110)
 *           /    \                                   /   \
 *          /      \                                 /     \
 *       (30)     (110)                          (60)       (150)
 *       /       /     \                         /  \        / 
 *     (20)   (80)     (150)                  (30)  (80)   (130)
 *            /  \     /                      /     /  \
 *          (70) (90)(130)                  (20)  (70)(90)
 *                  \                                    \
 *                 (100)                                (100)
 *
 **/

void test_leftRotate_given_treeA_should_rotate_to_treeB(void){
  Node* testTree = &node60;
  
  linkNode(&node60, &node30, &node110);
  linkNode(&node30, &node20, NULL);
  linkNode(&node110, &node80, &node150);
  linkNode(&node150, &node130, NULL);
  linkNode(&node80, &node70, &node90);
  linkNode(&node90, NULL, &node100);
  
  leftRotate(&testTree);

  TEST_ASSERT_TREE_LINK(&node110, &node60, &node150, testTree);
 //*********RIGHT SIDE*********************
  Node* rightNode = testTree->right;
  TEST_ASSERT_TREE_LINK(&node150, &node130, NULL, rightNode);
  
  //*********LEFT SIDE**********************
  Node* leftNode  = testTree->left;
  TEST_ASSERT_TREE_LINK(&node60, &node30, &node80, leftNode);
  TEST_ASSERT_TREE_LINK(&node30, &node20, NULL   , leftNode->left);
  TEST_ASSERT_TREE_LINK(&node80, &node70, &node90, leftNode->right);
  TEST_ASSERT_TREE_LINK(&node90, NULL   ,&node100, leftNode->right->right);
}

/**
 *  rightRotate should rotate the tree from tree A to tree B as shown below
 *  
 *            (70)                               (30)
 *           /    \                             /    \
 *          /      \                           /      \
 *       (30)       (90)                     (20)     (70)
 *       /  \      /    \                   /        /    \
 *     (20) (50) (80)  (100)             (10)     (50)    (90)
 *     /    /  \                                  /  \    /  \
 *  (10) (40) (60)                              (40)(60)(80)(100)
 *
 **/
void test_rightRotate_given_treeA_should_rotate_to_treeB(void){
  Node* testTree = &node70;
  
  linkNode(&node70, &node30, &node90);
  linkNode(&node30, &node20, &node50);
  linkNode(&node20, &node10, NULL);
  linkNode(&node50, &node40, &node60);
  linkNode(&node90, &node80, &node100);
  
  rightRotate(&testTree);
  
  TEST_ASSERT_TREE_LINK(&node30, &node20, &node70, testTree);
 
 //*********LEFT SIDE*********************
  Node* leftNode = testTree->left;
  TEST_ASSERT_TREE_LINK(&node20, &node10, NULL, leftNode);
  
  //*********RIGHT SIDE**********************
  Node* rightNode  = testTree->right;
  TEST_ASSERT_TREE_LINK(&node70, &node50, &node90, rightNode);
  TEST_ASSERT_TREE_LINK(&node50, &node40, &node60, rightNode->left);
  TEST_ASSERT_TREE_LINK(&node90, &node80, &node100, rightNode->right);

}

/**
 *  rightLeftRotate should rotate the tree from tree A to tree B as shown below
 *
 *  Tree A                                          Tree B
 *  
 *            (60)                                    (80)
 *           /    \                                   /   \
 *          /      \                                 /     \
 *       (30)     (110)                          (60)       (110)
 *       /       /     \                         /  \        /  \ 
 *     (20)   (80)     (150)                  (30)  (70)  (90)  (150)
 *            /  \     /                      /             \     /
 *          (70) (90)(130)                  (20)           (100)(130)
 *                  \  
 *                 (100)
 *
 **/
void test_rightLeftRotate_given_treeA_should_rotate_to_treeB(void){
  Node* testTree = &node60;
  
  linkNode(&node60, &node30, &node110);
  linkNode(&node30, &node20, NULL);
  linkNode(&node110, &node80, &node150);
  linkNode(&node150, &node130, NULL);
  linkNode(&node80, &node70, &node90);
  linkNode(&node90, NULL, &node100);  
  rightLeftRotate(&testTree);
  
  TEST_ASSERT_TREE_LINK(&node80, &node60, &node110, testTree);
 
 //*********RIGHT SIDE*********************
  Node* rightNode = testTree->right;
  TEST_ASSERT_TREE_LINK(&node110, &node90, &node150, rightNode);
  TEST_ASSERT_TREE_LINK(&node90 , NULL   , &node100, rightNode->left);
  TEST_ASSERT_TREE_LINK(&node150,&node130, NULL    , rightNode->right);
  
  //*********LEFT SIDE**********************
  Node* leftNode  = testTree->left;
  TEST_ASSERT_TREE_LINK(&node60 , &node30, &node70, leftNode);
  TEST_ASSERT_TREE_LINK(&node30 , &node20, NULL   , leftNode->left);
}

/**
 *  leftRightRotate should rotate the tree from tree A to tree B as shown below
 *  
 *            (70)                               (50)
 *           /    \                             /    \
 *          /      \                           /      \
 *       (30)       (90)                     (30)     (70)
 *       /  \      /    \                    / \      /   \
 *     (20) (50) (80)  (100)              (20)(40)  (60)  (90)
 *     /    /  \                          /               /  \
 *  (10) (40) (60)                      (10)            (80)(100)
 *
 **/
void test_leftRightRotate_given_treeA_should_rotate_to_treeB(void){
  Node* testTree = &node70;
  
  linkNode(&node70, &node30, &node90);
  linkNode(&node30, &node20, &node50);
  linkNode(&node20, &node10, NULL);
  linkNode(&node50, &node40, &node60);
  linkNode(&node90, &node80, &node100);
  
  leftRightRotate(&testTree);
  
  TEST_ASSERT_TREE_LINK(&node50, &node30, &node70, testTree);
 
 //*********LEFT SIDE*********************
  Node* leftNode = testTree->left;
  TEST_ASSERT_TREE_LINK(&node30, &node20, &node40, leftNode);
  TEST_ASSERT_TREE_LINK(&node20, &node10, NULL   , leftNode->left);\
  
  //*********RIGHT SIDE**********************
  Node* rightNode  = testTree->right;
  TEST_ASSERT_TREE_LINK(&node70, &node60, &node90, rightNode);
  TEST_ASSERT_TREE_LINK(&node90, &node80, &node100, rightNode->right);
}












