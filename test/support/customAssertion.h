#ifndef customAssertion_H
#define customAssertion_H

#include "unity.h"
#include "Node.h"

// ... can represent any arguement.
#define CUSTOM_TEST_FAIL(lineNo, msg, ...)                                                        \
                {                                                                                 \
                char buffer[256];                                                                 \
                sprintf(buffer, msg, ## __VA_ARGS__);                                             \
                UNITY_TEST_FAIL(lineNo,buffer);                                                   \
                }

#define TEST_ASSERT_EQUAL_NODE(expectedData, expectedBalanceFactor, actualNode);                   \
          customTestAssertNode(expectedData, expectedBalanceFactor, actualNode, __LINE__);
        
#define TEST_ASSERT_TREE_LINK(expectNode, expectLeft, expectRight, actualNode);                                     \
          customTestAssertTreeLink(expectNode, expectLeft, expectRight, actualNode, __LINE__);

void customTestAssertNode(int expectedData, int expectedBalanceFactor, Node* actualNode, int lineNumber);
void customTestAssertTreeLink(Node* expectNode, Node* expectLeft, Node* expectRight, Node* actualNode, int lineNumber);


#endif // customAssertion_H
