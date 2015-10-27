#include "unity.h"
#include "Node.h"
#include "customAssertion.h"

void setUp(void){}

void tearDown(void){}

/**
 *  createNode(3, 0) should create a Node as shown below
 *  
 *  ..................
 *  .balanceFactor: 0.
 *  .data:3          .
 *  ..................
 **/
void test_createNode_create_a_node_with_data_3(void){
	Node* testNode = createNode(3, 0);
  
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
	Node* rootNode  = createNode(10, 0);
	Node* leftNode  = createNode(5, 0);
	Node* rightNode = createNode(15, 0);
  
  Node* testNode = linkNode(rootNode,leftNode,rightNode);
  
  TEST_ASSERT_NOT_NULL(testNode);
  TEST_ASSERT_NOT_NULL(testNode->left);
  TEST_ASSERT_NOT_NULL(testNode->right);
  TEST_ASSERT_EQUAL_NODE(10, 0, testNode);
  TEST_ASSERT_EQUAL_NODE(5, 0, testNode->left);
  TEST_ASSERT_EQUAL_NODE(15, 0, testNode->right);
}
