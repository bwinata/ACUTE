/**************************************************************
 * ACUTE - Another C Unit Testing Environment
 * ------------------------------------------------------------
 * Decription:
 * 	List of assertions available to the client. These assertions
 * 	are to be used in conjuntion with the testing framework.
 *
 * Module	:	ACUTE Assertions
 * File		:	acuteAsserts.c
 *
 * Author	: 	Barry Winata
 * Date		:	25 November 2013
 * Contact	:	barry.winata@yahoo.com
 *
 **************************************************************/

#include "acuteAsserts.h"

/*
 * PREPROCESSOR DEFINITIONS
 * ======================================================
 */
#define TRUE	1
#define	FALSE	0

/*
 * PRIVATE FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_assert_print
 * ------------------------------------------------------
 * Print exception associated with assertion if condition
 * has not been met.
 *
 * IN:
 * 	- Line number of exception
 * 	- Pointer to exception string
 * OUT:
 * 	- N/A
 */
static void ACUTE_assert_print (int line, unsigned char * exception) {
	printf("%s at line %d\n", exception, line);
}

/*
 * PUBLIC FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_assert
 * ------------------------------------------------------
 * Checks if condition has been met. If not then assert
 * exception.
 *
 * IN:
 * 	- Result of condition
 * 	- Line number of where this function was called.
 * 	- Pointer to exception string.
 * OUT:
 * 	- N/A
 */
void ACUTE_assert (int result, int line, unsigned char * exception) {
	if (!(result)) {
		ACUTE_assert_print (line, exception);
	}
}

/*
 * FUNCTION: ACUTE_assert_true
 * ------------------------------------------------------
 * Checks if condition is true. If not, then assert exception
 *
 * IN:
 * 	- Result of condition
 * 	- Line number of where this function was called.
 * 	- Pointer to exception string.
 * OUT:
 * 	- N/A
 */
void ACUTE_assert_true (int result, int line, unsigned char * exception) {
	if (result != TRUE){
		ACUTE_assert_print (line, exception);
	}
}

/*
 * FUNCTION: ACUTE_assert_false
 * ------------------------------------------------------
 * Checks if condition has if false. If not then assert
 * exception.
 *
 * IN:
 * 	- Result of condition
 * 	- Line number of where this function was called.
 * 	- Pointer to exception string.
 * OUT:
 * 	- N/A
 */
void ACUTE_assert_false (int result, int line, unsigned char * exception) {
	if (result != FALSE) {
		ACUTE_assert_print (line, exception);
	}
}

/*
 * FUNCTION: ACUTE_assert_equal
 * ------------------------------------------------------
 * Checks if actual = expected. If not then assert
 * exception.
 *
 * IN:
 * 	- Acutal value produced
 * 	- Expected value
 * 	- Line number of where this function was called.
 * 	- Pointer to exception string.
 * OUT:
 * 	- N/A
 */
void ACUTE_assert_equal (int acutal, int expected, int line, unsigned char * exception) {
	if (acutal != expected) {
		ACUTE_assert_print (line, exception);
	}
}
/*
 * FUNCTION: ACUTE_assert_not_equal
 * ------------------------------------------------------
 * Checks if actual != expected. If not then assert
 * exception.
 *
 * IN:
 * 	- Actual value produced
 * 	- Expected value
 * 	- Line number of where this function was called.
 * 	- Pointer to exception string.
 * OUT:
 * 	- N/A
 */
void ACUTE_assert_not_equal (int actual, int expected, int line, unsigned char * exception) {
	if (actual == expected) {
		ACUTE_assert_print (line, exception);
	}
}


