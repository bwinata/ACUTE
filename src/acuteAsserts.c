#include "acuteAsserts.h"

static void acute_assert (int result, int line, char * exception, ...) {
	printf ("Acute Assert = %d\n", TEST_VALUE);
}

static void acute_assert_true (int result, int line, char * exception, ...) {
	printf ("Acute Assert True = %d\n", TEST_VALUE);
}

static void acute_assert_false (int result, int line, char * exception, ...) {
	printf ("Acute Assert False = %d\n", TEST_VALUE);
}

static void test_function (void) {
	printf ("This is a test function\n");
}
