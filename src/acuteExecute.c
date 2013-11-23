#include "acuteTest.h"

/*
 * PRIVATE FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_runTestMethods
 * ------------------------------------------------------
 * Runs all registered Test Cases. Progressively traverses through
 * the linked list of each
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */

static void ACUTE_runTestMethods (ACUTE_testMethod * testMethod) {
	while (testMethod != NULL) {
		printf ("Running Test Method: %s\n", testMethod->testMethodName);

		/* Execute Test Method */
		testMethod->testMethod ();

		/* Traverse along Test Method List */
		testMethod = testMethod->nextMethod;
	}
}

/*
 * FUNCTION: ACUTE_runTestCases
 * ------------------------------------------------------
 * Runs all registered Test Cases. Progressively traverses through
 * the linked list of each
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */

static void ACUTE_runTestCases (ACUTE_testSuite * testSuite, ACUTE_testCase * testCase, ACUTE_testMethod * testMethod) {
	while (testSuite != NULL) {
		testCase = testSuite->testCase;
		testMethod = testCase->testCaseHead;

		printf ("Running Test Case ----> %s\n", testCase->testCaseName);
		printf ("------------------------------------------------\n");
		ACUTE_runTestMethods (testMethod);

		/* Traverse along Test Suite List */
		testSuite = testSuite->next;
	}
}

/*
 * PUBLIC FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_run
 * ------------------------------------------------------
 * Runs all registered Test Cases. Progressively traverses through
 * the linked list of each
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */

void ACUTE_run (void) {
	/* Get access to General Test Suite */
	ACUTE_testSuite * entryTestSuite = globalHeadQueue;
	ACUTE_testCase * entryTestCase = NULL;
	ACUTE_testMethod * entryTestMethod = NULL;

	printf ("==================================================\n");
	printf ("ACUTE: Unit Testing Framework\n");
	printf ("==================================================\n");
	ACUTE_runTestCases (entryTestSuite, entryTestCase, entryTestMethod);
	printf ("==================================================\n");
	printf ("Finished!\n");
	printf ("==================================================\n");
}
