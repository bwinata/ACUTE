/**************************************************************
 * ACUTE
 *
 * Decription:
 * Assertion definitions
 *
 * Author	: 	Barry Winata
 * Date		:	11 November 2013
 *
 **************************************************************/

/*
 * PREPROCESSOR CONSTATNTS
 * ======================================================
 */
#define		TEST_VALUE	15

/*
 * BOOLEAN TESTS
 * ======================================================
 */
#define		ACUTE_ASSERT (condition, message)			acute_assert (condition, __LINE__, "Exception: Condition has not met", ...)
#define		ACUTE_ASSERT_TRUE (condition, message)		acute_assert_true (condition, __LINE__, "Exception: Condition is FALSE but is expected to be TRUE", ...)
#define 	ACUTE_ASSERT_FALSE (condition, message)		acute_assert_false (condition, __LINE__, "Exception: Condition is TRUE but is expected to be FALSE", ...)
#define		ACUTE_ASSERT_NULL (pointer, message)		acute_assert ((pointer == NULL), __LINE__, "Exception: Pointer is NOT Null", ...)
#define 	ACUTE_ASSERT_NOT_NULL (pointer, message)	acute_assert ((pointer != NULL), __LINE__, "Exception: Pointer is NULL", ...)

/*
 * EQUALITY TESTS
 * ======================================================
 */

#define		ACUTE_ASSERT_EQUAL (actual, expected, message)		accute_assert_equal (actual, expected, __LINE__, "Expected: Values are not equal", ...)
#define		ACUTE_ASSERT_NOT_EQUAL (actual, expected, message)	accute_assert_not_equal (actual, expected, __LINE__, "Expected: Values are equal", ...)
#define		ACUTE_ASSERT_STRING_EQUAL (actual, expected)		accute_assert_string_equal (actual, expected, __LINE__, "Expected: Strings are not equal")
#define		ACUTE_ASSERT_STRING_NOT_EQUAL (actual, expected)	accute_assert_string_not_equal (actual, expected, __LINE__, "Expected: Strings are equal")


/*
 * PROTOTYPE DEFINITIONS
 * ======================================================
 */

extern void acute_assert (int result, int line, char * exception, ...);
extern void acute_assert_true (int result, int line, char * exception, ...);
extern void acute_assert_false (int result, int line, char * exception, ...);




