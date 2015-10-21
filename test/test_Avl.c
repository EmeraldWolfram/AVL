#include "unity.h"
#include "Avl.h"
#include "customAssertion.h"
#include "Node.h"

Node  node10, node20, node30, node40, node50, node60, node70, node80, node90;
Node  node100, node110, node120, node130, node140, node150, node160, node170;
Node  node180, node190;

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
 *  Adding node30 to node10 should increase the balanceFactor of node10 to 1
 *
 *    (10)
 *      \
 *      (30)
 **/
void test_avlAdd_given_10_add_30_should_place_at_right_side(void){
  Node* root = &node10;
  TEST_ASSERT_EQUAL(0, root->balanceFactor);
	int i = avlAdd(&root, &node30);
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_TREE_LINK(&node10, NULL, &node30, root);
}


/**
 *  Adding node60 to Tree A should remain the balanceFactor of node20 as 1
 *
 *  Tree A            Tree B
 *    (20)              (20)
 *    /  \              /  \
 *  (10)  (40)  >>   (10)  (40)
 *        /                /  \
 *      (30)            (30)  (60)
 *
 **/
void test_avlAdd_given_treeA_add_60_should_become_tree_B(void){
  Node* root = &node20;
  linkNode(&node20, &node10, &node40);
  linkNode(&node40, &node30, NULL);
  root->balanceFactor = 1;
  
  TEST_ASSERT_EQUAL(1, root->balanceFactor);
	int i = avlAdd(&root, &node60);
  TEST_ASSERT_EQUAL(1, i);
  TEST_ASSERT_TREE_LINK(&node20, &node10, &node40, root);
  TEST_ASSERT_TREE_LINK(&node40, &node30, &node60, root->right);
}

/**
 *  Adding node10 to Tree A should reduce the balanceFactor of node40 to 0
 *
 *  Tree A            Tree B
 *    (40)              (40)
 *    /  \              /  \
 *  (20) (60)  >>   (20)  (60)
 *       /          /    /
 *     (50)       (10) (50)
 *
 **/
void test_avlAdd_given_treeA_add_10_should_become_tree_B(void){
  Node* root = &node40;
  linkNode(&node40, &node20, &node60);
  linkNode(&node60, &node50, NULL);
  root->balanceFactor = 1;
  
  TEST_ASSERT_EQUAL(1, root->balanceFactor);
	int i = avlAdd(&root, &node10);
  TEST_ASSERT_EQUAL(0, i);
  TEST_ASSERT_TREE_LINK(&node40, &node20, &node60, root);
  TEST_ASSERT_TREE_LINK(&node20, &node10, NULL, root->left);
}



