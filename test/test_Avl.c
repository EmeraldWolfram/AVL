#include "unity.h"
#include "Avl.h"
#include "Rotation.h"
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
//TEST_ASSERT_TREE_LINK(Node* expectNode, Node* expectLeft, Node* expectRight, Node* actualNode)
  TEST_ASSERT_TREE_LINK(&node10, NULL, &node30, root);
}


/**
 *  Adding node60 to Tree A should link the node60 at rightest bottom and 
 *  form tree B.
 *
 *  The balance factor of node20 should remain 1
 *  Similarly, balance factor of node40 should increase from -1 to 0
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
  root->balanceFactor   = 1;
  node40.balanceFactor  = -1;
  
  TEST_ASSERT_EQUAL(1, root->balanceFactor);
	int i = avlAdd(&root, &node60);
  TEST_ASSERT_EQUAL(0, i);
  TEST_ASSERT_TREE_LINK(&node20, &node10, &node40, root);
  TEST_ASSERT_TREE_LINK(&node40, &node30, &node60, root->right);
//TEST_ASSERT_EQUAL_NODE(expectedData, expectedBalanceFactor, actualNode);
  TEST_ASSERT_EQUAL_NODE(20, 1, &node20);
  TEST_ASSERT_EQUAL_NODE(40, 0, &node40);
}

/**
 *  Adding node10 to Tree A should link node10 to most left and most bottom
 *  to form Tree B
 *
 *  Balance Factor that should change:
 *  1. node20     from 0 to -1
 *  2. node40     from 1 to 0
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
  
  TEST_ASSERT_EQUAL_NODE(20, -1, &node20);
  TEST_ASSERT_EQUAL_NODE(40,  0, &node40);
}

/****************************************************
 *  Test for Case(2,-1,0)                           *
 *                                                  *
 *  Tree A                                          *
 *    (60)        Balance Factor:                   *
 *       \        1. node60     +2                  *
 *       (90)     2. node90     -1                  *
 *       /        3. node80      0                  *
 *    (80)                                          *
 ****************************************************
 *  rightLeftRotate will be called and form tree B  *
 ****************************************************
 *                                                  *
 *  Tree B                                          *
 *    (80)        Balance Factor:                   *
 *    /  \        1. node60      0                  *
 *  (60)(90)      2. node90      0                  *
 *                3. node80      0                  *
 ****************************************************/
void test_avlAdd_calling_rightLeftRotate_given_treeA_with_case2_neg1_0_should_transform_to_treeB(void){
  Node* testTree = &node60;
    
  int i = avlAdd(&testTree, &node90);
  i = avlAdd(&testTree, &node80);
  
  TEST_ASSERT_TREE_LINK(&node80, &node60, &node90, testTree);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE(90,  0, &node90);
  TEST_ASSERT_EQUAL_NODE(80,  0, &node80);

}

/****************************************************
 *  Test for case (2,-1,-1)                         *
 *                                                  *
 *  Tree A            Balance Factor:               *
 *    (60)            1. node60     +2              *
 *    /  \            2. node40      0              *
 *  (40) (100)        3. node100    -1              *
 *       /   \        4. node80     -1              *
 *    (80)   (120)    5. node120     0              *
 *    /               6. node70      0              *
 * (70)                                             *
 ****************************************************
 *  rightLeftRotate will be called and form tree B  *
 ****************************************************
 *  After Left Rotation, Tree A become Tree B       *
 *                                                  *
 *  Tree B            Balance Factor:               *
 *      (80)          1. node60      0              *
 *     /    \         2. node40      0              *
 *  (60)    (100)     3. node100    +1              *
 *  /  \       \      4. node80      0              *
 *(40)(70)    (120)   5. node120     0              *
 *                    6. node70      0              *
 *                                                  *
 ****************************************************/
void test_avlAdd_calling_rightLeftRotate_given_treeA_with_case2_neg1_neg1_should_transform_to_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node100);
  i = avlAdd(&testTree, &node80);
  i = avlAdd(&testTree, &node120);
  i = avlAdd(&testTree, &node70);
  
  TEST_ASSERT_TREE_LINK( &node80, &node60, &node100, testTree);
  TEST_ASSERT_TREE_LINK( &node60, &node40,  &node70, testTree->left);
  TEST_ASSERT_TREE_LINK(&node100,    NULL, &node120, testTree->right);
  TEST_ASSERT_EQUAL_NODE( 80,  0, &node80);
  TEST_ASSERT_EQUAL_NODE( 60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE(100,  1, &node100);
  TEST_ASSERT_EQUAL_NODE( 40,  0, &node40);
  TEST_ASSERT_EQUAL_NODE( 70,  0, &node70);
  TEST_ASSERT_EQUAL_NODE(120,  0, &node120);
}


/********************************************************
 *  Test for case (2,-1,1)                             *
 *                                                      *
 *      Tree A                  Balance Factor:         *
 *         (80)                 1. node80     +2        *
 *        /   \                 2. node60      0        *
 *    (60)    (120)             3. node120    -1        *
 *            /   \             4. node100    +1        *
 *         (100) (160)          5. node160     0        *
 *             \                6. node110     0        *
 *            (110)                                     *
 ********************************************************
 *  After Rotation, Tree A become Tree B                *
 *                                                      *
 *      Tree B                    Balance Factor:       *
 *             (100)              1. node80     -1      *
 *            /    \              2. node60      0      *
 *          /       \             3. node120     0      *
 *       (80)       (120)         4. node100     0      *
 *      /           /   \         5. node160     0      *
 *   (60)        (110) (160)      6. node110     0      *
 ********************************************************/
void test_avlAdd_calling_rightLeftRotate_given_treeA_with_case2_neg1_1_should_transform_to_treeB(void){
  Node* testTree = &node80;
  int i = avlAdd(&testTree, &node60);
  i = avlAdd(&testTree, &node120);
  i = avlAdd(&testTree, &node100);
  i = avlAdd(&testTree, &node160);
  i = avlAdd(&testTree, &node110);
  
  TEST_ASSERT_TREE_LINK(&node100, &node80, &node120, testTree);
  TEST_ASSERT_TREE_LINK( &node80, &node60,     NULL, testTree->left);
  TEST_ASSERT_TREE_LINK(&node120,&node110, &node160, testTree->right);
  TEST_ASSERT_EQUAL_NODE( 80, -1, &node80);
  TEST_ASSERT_EQUAL_NODE( 60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE(120,  0, &node120);
  TEST_ASSERT_EQUAL_NODE(100,  0, &node100);
  TEST_ASSERT_EQUAL_NODE(160,  0, &node160);
  TEST_ASSERT_EQUAL_NODE(110,  0, &node110);
}

/****************************************************
 *  Test for Case(-2,1,0)                           *
 *                                                  *
 *  Tree A                                          *
 *    (60)        Balance Factor:                   *
 *    /           1. node60     -2                  *
 * (40)           2. node40     +1                  *
 *    \           3. node50      0                  *
 *    (50)                                          *
 ****************************************************
 *  leftRightRotate will be called and form tree B  *
 ****************************************************
 *                                                  *
 *  Tree B                                          *
 *    (50)        Balance Factor:                   *
 *    /  \        1. node60      0                  *
 *  (40)(60)      2. node40      0                  *
 *                3. node50      0                  *
 ****************************************************/
void test_avlAdd_calling_leftRightRotate_given_treeA_with_caseNeg2_1_0_should_transform_to_treeB(void){
  Node* testTree = &node60;
    
  int i = avlAdd(&testTree, &node40);
  i = avlAdd(&testTree, &node50);
  
  TEST_ASSERT_TREE_LINK(&node50, &node40, &node60, testTree);
  TEST_ASSERT_EQUAL_NODE(60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE(40,  0, &node40);
  TEST_ASSERT_EQUAL_NODE(50,  0, &node50);

}

/****************************************************
 *  Test for case (-2,1,-1)                         *
 *                                                  *
 *  Tree A            Balance Factor:               *
 *       (60)         1. node60     -2              *
 *      /   \         2. node30     +1              *
 *    (30)  (80)      3. node80      0              *
 *    /  \            4. node20      0              *
 * (20) (50)          5. node50     -1              *
 *     /              6. node40      0              *
 *   (40)                                           *
 ****************************************************
 *  leftRightRotate will be called and form tree B  *
 ****************************************************
 *  After Rotation, Tree A become Tree B            *
 *                                                  *
 *  Tree B            Balance Factor:               *
 *      (50)          1. node60     +1              *
 *     /    \         2. node30      0              *
 *  (30)    (60)      3. node80      0              *
 *  /  \       \      4. node20      0              *
 *(20)(40)    (80)    5. node50      0              *
 *                    6. node40      0              *
 *                                                  *
 ****************************************************/
void test_avlAdd_calling_leftRightRotate_given_treeA_with_caseNeg2_1_neg1_should_transform_to_treeB(void){
  Node* testTree = &node60;
  int i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node80);
  i = avlAdd(&testTree, &node20);
  i = avlAdd(&testTree, &node50);
  i = avlAdd(&testTree, &node40);
  
  TEST_ASSERT_TREE_LINK(&node50, &node30, &node60, testTree);
  TEST_ASSERT_TREE_LINK(&node30, &node20, &node40, testTree->left);
  TEST_ASSERT_TREE_LINK(&node60,    NULL, &node80, testTree->right);
  TEST_ASSERT_EQUAL_NODE(60, 1, &node60);
  TEST_ASSERT_EQUAL_NODE(30, 0, &node30);
  TEST_ASSERT_EQUAL_NODE(80, 0, &node80);
  TEST_ASSERT_EQUAL_NODE(20, 0, &node20);
  TEST_ASSERT_EQUAL_NODE(50, 0, &node50);
  TEST_ASSERT_EQUAL_NODE(40, 0, &node40);
}


/********************************************************
 *  Test for case (-2,1,1)                              *
 *                                                      *
 *      Tree A                  Balance Factor:         *
 *         (80)                 1. node80     -2        *
 *        /   \                 2. node50     +1        *
 *    (50)    (120)             3. node120     0        *
 *    /  \                      4. node30      0        *
 * (30) (60)                    5. node60     +1        *
 *         \                    6. node70      0        *
 *        (70)                                          *
 ********************************************************
 *  leftRightRotate will be called and form tree B      *
 ********************************************************
 *                                                      *
 *      Tree B                    Balance Factor:       *
 *        (60)                    1. node80      0      *
 *       /   \                    2. node50     -1      *
 *    (50)  (80)                  3. node120     0      *
 *    /     /  \                  4. node30      0      *
 *  (30)  (70) (120)              5. node60      0      *
 *                                6. node70      0      *
 ********************************************************/
void test_avlAdd_calling_leftRightRotate_given_treeA_with_caseNeg2_1_1_should_transform_to_treeB(void){
  Node* testTree = &node80;
  int i = avlAdd(&testTree, &node50);
  i = avlAdd(&testTree, &node120);
  i = avlAdd(&testTree, &node30);
  i = avlAdd(&testTree, &node60);
  i = avlAdd(&testTree, &node70);
  
  TEST_ASSERT_TREE_LINK(&node60, &node50, &node80, testTree);
  TEST_ASSERT_TREE_LINK(&node50, &node30,    NULL, testTree->left);
  TEST_ASSERT_TREE_LINK(&node80, &node70,&node120, testTree->right);
  TEST_ASSERT_EQUAL_NODE( 80,  0, &node80);
  TEST_ASSERT_EQUAL_NODE( 50, -1, &node50);
  TEST_ASSERT_EQUAL_NODE(120,  0, &node120);
  TEST_ASSERT_EQUAL_NODE( 30,  0, &node30);
  TEST_ASSERT_EQUAL_NODE( 60,  0, &node60);
  TEST_ASSERT_EQUAL_NODE( 70,  0, &node70);
}

