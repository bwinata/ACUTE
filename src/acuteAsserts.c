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
static void ACUTE_assert_print (int line, unsigned char * exception) {
	printf("%s at line %d\n", exception, line);
}

/*
 * PUBLIC FUNCTIONS DEFINITIONS
 * ======================================================
 */
void ACUTE_assert (int result, int line, unsigned char * exception) {
	if (!(result)) {
		ACUTE_assert_print (line, exception);
	}
}

void ACUTE_assert_true (int result, int line, unsigned char * exception) {
	if (result != TRUE){
		ACUTE_assert_print (line, exception);
	}
}

void ACUTE_assert_false (int result, int line, unsigned char * exception) {
	if (result != FALSE) {
		ACUTE_assert_print (line, exception);
	}
}

void ACUTE_assert_equal (int acutal, int expected, int line, unsigned char * exception) {
	if (acutal != expected) {
		ACUTE_assert_print (line, exception);
	}
}

void ACUTE_assert_not_equal (int actual, int expected, int line, unsigned char * exception) {
	if (actual == expected) {
		ACUTE_assert_print (line, exception);
	}
}


