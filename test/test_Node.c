#include "unity.h"
#include "Node.h"
#include "customAssertion.h"

void setUp(void){}

void tearDown(void){}

/**
 *  createNode(3) should create a Node as shown below
 *  
 *  ..................
 *  .balanceFactor: 0.
 *  .data:3          .
 *  ..................
 **/
void test_createNode_create_a_node_with_data_3(void){
	Node* testNode = createNode(3);
  
  TEST_ASSERT_NOT_NULL(testNode);
  TEST_ASSERT_NULL(testNode->left);
  TEST_ASSERT_NULL(testNode->right);
  TEST_ASSERT_EQUAL_NODE(3, 0, testNode);
}

/**
 *  linkNode should link two child into the root with linkNode(root, leftNode, rightNode)
 *  as shown below:
 *  
 *            rootNode
 *            /     \
 *     leftNode     rightNode
 *
 *  In this test, the tree will be
 *  
 *                .............  
 *                .data:  10  .
 *                .............
 *                /           \
 *       ..............     ..............
 *       .data:   5   .     .data:  15   .
 *       ..............     ..............
 *
 **/
void test_linkNode_given_3_node_should_link_together(void){
	Node* rootNode  = createNode(10);
	Node* leftNode  = createNode(5);
	Node* rightNode = createNode(15);
  
  Node* testNode = linkNode(rootNode,leftNode,rightNode);
  
  TEST_ASSERT_NOT_NULL(testNode);
  TEST_ASSERT_NOT_NULL(testNode->left);
  TEST_ASSERT_NOT_NULL(testNode->right);
  TEST_ASSERT_EQUAL_NODE(10, 0, testNode);
  TEST_ASSERT_EQUAL_NODE(5, 0, testNode->left);
  TEST_ASSERT_EQUAL_NODE(15, 0, testNode->right);
}

/**
 *  initializeTreeForLeftTest should initialize a tree as shown below
 *  
 *            (60)                               
 *           /    \                         
 *          /      \                         
 *       (30)     (110)                       
 *       /       /     \                       
 *     (20)   (80)     (150)                
 *            /  \     /          
 *          (70) (90)(130)
 *                  \  
 *                 (100)
 *
 **/
void test_initializeTreeForLeftTest(void){
  Node* testNode5 = initializeTreeForLeftTest();
  
  TEST_ASSERT_NOT_NULL(testNode5);
  TEST_ASSERT_EQUAL(60,   testNode5->data);
  TEST_ASSERT_EQUAL(30,   testNode5->left->data);
  TEST_ASSERT_EQUAL(110,  testNode5->right->data);
  
  TEST_ASSERT_EQUAL(20,   testNode5->left->left->data);
  TEST_ASSERT_EQUAL(80,   testNode5->right->left->data);
  TEST_ASSERT_EQUAL(150,  testNode5->right->right->data);
  
  TEST_ASSERT_EQUAL(70,   testNode5->right->left->left->data);
  TEST_ASSERT_EQUAL(90,   testNode5->right->left->right->data);
  TEST_ASSERT_EQUAL(130,  testNode5->right->right->left->data);
  
  TEST_ASSERT_EQUAL(100,  testNode5->right->left->right->right->data);
}

/**
 *  initializeTreeForRightTest should initialize a tree as shown below
 *  
 *            (60)                               
 *           /    \                         
 *          /      \                         
 *       (30)       (90)                       
 *       /  \      /    \                       
 *     (15) (45) (75)  (115)                
 *     /    /  \          
 *  (10) (36) (50)
 *
 **/
void test_initializeTreeForRightTest(void){
  Node* testNode5 = initializeTreeForRightTest();
  
  TEST_ASSERT_NOT_NULL(testNode5);
  TEST_ASSERT_EQUAL(60,   testNode5->data);
  TEST_ASSERT_EQUAL(30,   testNode5->left->data);
  TEST_ASSERT_EQUAL(90,  testNode5->right->data);
  
  TEST_ASSERT_EQUAL(15,   testNode5->left->left->data);
  TEST_ASSERT_EQUAL(45,   testNode5->left->right->data);
  TEST_ASSERT_EQUAL(75,   testNode5->right->left->data);
  TEST_ASSERT_EQUAL(115,  testNode5->right->right->data);
  
  TEST_ASSERT_EQUAL(10,   testNode5->left->left->left->data);
  TEST_ASSERT_EQUAL(50,   testNode5->left->right->right->data);
  TEST_ASSERT_EQUAL(36,  testNode5->left->right->left->data);
}