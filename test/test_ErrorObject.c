#include "unity.h"
#include "ErrorObject.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_ThrowError_throw_ERR_DUPLICATED_VALUE_should_get_an_error_object_containing_them(void){
  ErrorObject* err;
  Try{
    ThrowError(ERR_DUPLICATED_VALUE, "Two node with same value are detected");
    TEST_FAIL_MESSAGE("Expecting ERR_DUPLICATED_VALUE but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL(ERR_DUPLICATED_VALUE, err->errorCode);
    TEST_ASSERT_EQUAL_STRING("Two node with same value are detected",  err->errorMsg);
    freeError(err);
  }
}
