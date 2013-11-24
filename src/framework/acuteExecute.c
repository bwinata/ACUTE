/**************************************************************
 * ACUTE - Another C Unit Testing Environment
 * ------------------------------------------------------------
 * Decription:
 * 	Execution framework responsible for verifying validity of
 * 	Test Cases / Methods and proceeds to run Unit Tests. Generates
 * 	output summary on the command line.
 *
 * Module	:	ACUTE Framework
 * File		:	acuteExecute.c
 *
 * Author	: 	Barry Winata
 * Date		:	14 November 2013
 * Contact	:	barry.winata@yahoo.com
 *
 **************************************************************/

#include "acuteFramework.h"

/*
 * PRIVATE FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_getNumTestCases
 * ------------------------------------------------------
 * Gets number of registered Test Cases.
 *
 * IN:
 * 	- Head node to General Test Suite.
 * OUT:
 * 	- Number of available Test Cases.
 */
static unsigned int ACUTE_getNumTestCases (ACUTE_testSuite * headSuite) {
	static int counter = 0;
	if (headSuite == NULL)
		return counter;
	else {
		counter++;
		return ACUTE_getNumTestCases (headSuite->next);
	}
}

/*
 * FUNCTION: ACUTE_getNumTestMethods
 * ------------------------------------------------------
 * Gets total number of registered Test Methods in all
 * available Test Cases.
 *
 * IN:
 * 	- Head node to General Test Suite.
 * OUT:
 * 	- Total number of available Test Methods
 */
static unsigned int ACUTE_getNumTestMethods (ACUTE_testSuite * headSuite) {
	static int counter = 0;

	while (headSuite != NULL) {
		while (headSuite->testCase->testCaseHead != NULL) {
			counter++;
			headSuite->testCase->testCaseHead = headSuite->testCase->testCaseHead->nextMethod;
		}
		headSuite = headSuite->next;
	}
	return counter;
}

/*
 * FUNCTION: ACUTE_runTestMethods
 * ------------------------------------------------------
 * Runs all registered Test Methods. Progressively traverses through
 * the linked list of each Test Suite node and executes each
 * method.
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
 * the general linked list of each suite.
 *
 * IN:
 * 	- Pointer to Test Suite
 * 	- Pointer to Test Case derived from Test Suite
 * 	- Pointer to Test Method derived from Test Case
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
 * the linked list of each Test Case and executes asscoiated Test
 * Methods.
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

	unsigned int noTestCases, noTestMethods, noAssertions;

	printf ("\n==================================================\n");
	printf ("ACUTE: Unit Testing Framework\n");
	printf ("==================================================\n");
	printf ("No. Test Cases    :    %d\n", (noTestCases = ACUTE_getNumTestCases (entryTestSuite)));
	printf ("No. Test Methods  :    %d\n", (noTestMethods = ACUTE_getNumTestMethods (entryTestSuite)));
	printf ("No. Assertions    :    0\n", (noAssertions = 0));
	printf ("==================================================\n");

	if (!noTestCases)
		printf ("\n**No Test Cases to process. Please register a valid Test Case and try again.**\n\n");
	else if (!noTestMethods)
		printf ("\n**No Test Methods to process. Please register a valid Test Method and try again.**\n\n");
	else
		ACUTE_runTestCases (entryTestSuite, entryTestCase, entryTestMethod);

	printf ("==================================================\n");
	printf ("ACUTE: Finished!\n");
	printf ("==================================================\n");

	/* Exit Safely - prevents subsequent funtions running after. This function must execute at the end */
	exit (0);
}

/*
 * UNIT TESTS
 * ======================================================
 */

/*
 * FUNCTION: myDummyTestMethod
 * ------------------------------------------------------
 * Dummy Test Method
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void myDummyTestMethod (void) {
	printf ("Hello World, this is a test function\n");
}

/*
 * FUNCTION: ACUTE_unitTest__run
 * ------------------------------------------------------
 * Tests if Test Cases / Methods are valid and executes
 * respective methods.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_unitTest__run (void) {
	/* Initialise Global Head to NULL */
	globalHeadQueue = NULL;

	ACUTE_testSuite * myTestSuite1 = ACUTE_createTestCase ("Test Case 1");
	ACUTE_testSuite * myTestSuite2 = ACUTE_createTestCase ("Test Case 2");

	ACUTE_createTestMethod (myTestSuite1, "Test Method 1", myDummyTestMethod);

	ACUTE_run ();
}
