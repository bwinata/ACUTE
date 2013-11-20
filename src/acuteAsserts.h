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

#ifndef ACUTEASSERTS_H_
#define ACUTEASSERTS_H_

#include "acuteTest.h"

/*
 * PREPROCESSOR DEFINITIONS
 * ======================================================
 */


/*
 * BOOLEAN TESTS
 * ======================================================
 */
#define		ACUTE_ASSERT(condition)						ACUTE_assert (condition, __LINE__, "ACUTE Exception: Condition has not been met")
#define		ACUTE_ASSERT_TRUE(condition)				ACUTE_assert_true (condition, __LINE__, "ACUTE Exception: Condition is FALSE but is expected to be TRUE")
#define 	ACUTE_ASSERT_FALSE(condition)				ACUTE_assert_false (condition, __LINE__, "ACUTE Exception: Condition is TRUE but is expected to be FALSE")
#define		ACUTE_ASSERT_NULL(pointer)					ACUTE_assert ((pointer == NULL), __LINE__, "ACUTE Exception: Pointer is NOT Null")
#define 	ACUTE_ASSERT_NOT_NULL(pointer)				ACUTE_assert ((pointer != NULL), __LINE__, "ACUTE Exception: Pointer is NULL")

/*
 * EQUALITY TESTS
 * ======================================================
 */

#define		ACUTE_ASSERT_EQUAL(actual, expected)				ACUTE_assert_equal (actual, expected, __LINE__, "ACUTE Expected: Values are not equal")
#define		ACUTE_ASSERT_NOT_EQUAL(actual, expected)			ACUTE_assert_not_equal (actual, expected, __LINE__, "ACUTE Expected: Values are equal")
#define		ACUTE_ASSERT_STRING_EQUAL(actual, expected)			ACUTE_assert_string_equal (actual, expected, __LINE__, "ACUTE Expected: Strings are not equal")
#define		ACUTE_ASSERT_STRING_NOT_EQUAL(actual, expected)		ACUTE_assert_string_not_equal (actual, expected, __LINE__, "ACUTE Expected: Strings are equal")


/*
 * PUBLIC FUNCTION DECLARATIONS
 * ======================================================
 */


#endif /* ACUTEASSERTS_H_ */


