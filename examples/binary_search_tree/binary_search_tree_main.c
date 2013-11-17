/**************************************************************
 * Doubly Linked List
 *
 * Decription:
 * This example provides a means to test and verify
 * the testing framework.
 *
 * Author	: 	Barry Winata
 * Date		:	11 November 2013
 *
 **************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "acuteAsserts.h"

void test_variable_args (int num, ...) {
	va_list arguments;

	double sum = 0;

	va_start (arguments, num);

	//printf ("--->%s\n", va_arg (arguments, char *));

	va_end (arguments);
}

int main (int argc, char ** argv) {

	test_variable_args (5);

	printf ("Size of char = %d\n", sizeof (char));
	printf ("Size of int = %d\n", sizeof (int));
	printf ("Size of short = %d\n", sizeof (short));
	printf ("Size of long = %d\n", sizeof (long));
	printf ("Size of double = %d\n", sizeof (double));
	printf ("Size of float = %d\n", sizeof (float));

	printf ("-->%d", TEST_VALUE);

	return 0;
}


