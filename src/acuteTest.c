#include "acuteTest.h"
#include "acuteException.h"

/*
 * PREPROCESSOR DEFINITIONS
 * ======================================================
 */
#define GENERAL_TEST_QUEUE_NAME		"General Test Case Queue"

/*
 * STRUCTURE DEFINITIONS
 * ======================================================
 * NB: Placed in .c to hide internal data structure to client.
 * References to structures are made in corresponding header
 * file
 */

/*
 * STRUCTURE: ACUTE_testMethod
 * ------------------------------------------------------
 * The test method to be executed during testing. Each method
 * must be associated with a test case. Each method that is
 * created is subsequently pushed to the end of the specified
 * Test Case queue (FIFO).
 */
typedef struct __ACUTE_TEST_METHOD__ {
	unsigned char * testMethodName;
	struct __ACUTE_TEST_CASE__ * testCase;
	void (*testMethod) (void);
	struct __ACUTE_TEST_METHOD__ * nextMethod;
	struct __ACUTE_TEST_METHOD__ * prevMethod;
} ACUTE_testMethod;

/*
 * STRUCTURE: ACUTE_testCase
 * -------------------------------------------------------
 * Each Test Case created must contain at least one Test
 * Method. Every Test Case is subsequently pushed to the end of
 * the specified Test Suite queue (FIFO).
 */
typedef struct __ACUTE_TEST_CASE__ {
	unsigned char * testCaseName;
	ACUTE_testMethod * testCaseHead;
	ACUTE_testMethod * testSetup;
	ACUTE_testMethod * testTearDown;
} ACUTE_testCase;

/*
 * STRUCTURE: ACUTE_testSuite
 * ------------------------------------------------------
 */
typedef struct __ACUTE_TEST_SUITE__ {
	unsigned char * testSuiteName;
	ACUTE_testCase * testCase;
	struct __ACUTE_TEST_SUITE__ * next;
	struct __ACUTE_TEST_SUITE__ * prev;
} ACUTE_testSuite;

/*
 * GLOBAL VARIABLES
 * ======================================================
 */
static ACUTE_testSuite * globalHeadQueue = NULL;

/*
 * PRIVATE FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_insertTestCaseIntoQueue
 * ------------------------------------------------------
 * Appends Test Suite containing test case to end of queue of
 * the General Test Suite Queue. This allows the Test Runner
 * to traverse this list starting from the Head Suite until completion
 * reaching the final suite to be tested.
 *
 * IN:
 * 	- Test Suite to be appended at end of General Test Suite Queue
 * OUT:
 * 	- N/A
 */
static void ACUTE_insertTestCaseIntoQueue (ACUTE_testSuite * testSuite) {
	ACUTE_testSuite * tempSuite = globalHeadQueue;
	while (tempSuite != NULL) {
		tempSuite = tempSuite->next;
	}
	tempSuite->next = testSuite;
	testSuite->prev = tempSuite;
}

/*
 * FUNCTION: ACUTE_insertTestMethodIntoQueue
 * ------------------------------------------------------
 * Inserts new Test Method into existing queue. Checks if a
 * Test Case is available, and if so, traverses through its
 * head node Test Case and attaches the method to the end.
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
static void ACUTE_insertTestMethodIntoQueue (ACUTE_testMethod * testMethod) {
	ACUTE_testMethod * tempMethod = (testMethod->testCase)->testCaseHead;
	while (tempMethod != NULL) {
		tempMethod = tempMethod->nextMethod;
	}
	tempMethod->nextMethod = testMethod;
	testMethod->prevMethod = tempMethod;
}

/*
 * FUNCTION: ACUTE_createTestSuite
 * ------------------------------------------------------
 * Creates a Test Suite that contains a link to a specified
 * Test Case.
 *
 * IN:
 * 	- Newly created Test Case
 * 	- Test Suite Name
 * OUT:
 * 	- Created Test Suite
 */
static ACUTE_testSuite * ACUTE_createTestSuite (ACUTE_testCase * testCase, char * testSuiteName) {
	ACUTE_testSuite * queue = (ACUTE_testSuite *) malloc (sizeof (ACUTE_testSuite));

	queue->testSuiteName = testSuiteName;
	queue->testCase = testCase;
	queue->next = NULL;
	queue->prev = NULL;

	return queue;
}

/*
 * FUNCTION: ACUTE_queueTestCase
 * ------------------------------------------------------
 * Queues newly created Test Case at the end of the Test
 * Suite linked list.
 *
 * IN:
 * 	- Test Case
 * OUT:
 * 	- N/A
 */
static void ACUTE_queueTestCase (ACUTE_testCase * testCase) {
	if (globalHeadQueue == NULL) {
		globalHeadQueue = ACUTE_createTestSuite (testCase, GENERAL_TEST_QUEUE_NAME);
	} else {
		ACUTE_insertTestCaseIntoQueue (ACUTE_createTestSuite (testCase, testCase->testCaseName));
	}
}

/*
 * FUNCTION: ACUTE_queueTestMethod
 * ------------------------------------------------------
 * Queues Test Method at the end of the Test Case linked list
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
static void ACUTE_queueTestMethod (ACUTE_testMethod * testMethod) {
	if ((testMethod->testCase)->testCaseHead == NULL) {
		(testMethod->testCase)->testCaseHead = testMethod;
	} else {
		ACUTE_insertTestMethodIntoQueue (testMethod);
	}
}

/*
 * PUBLIC FUNCTIONS DEFINITIONS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_createTestCase
 * ------------------------------------------------------
 * Queues Test Method at the end of the Test Case linked list
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
ACUTE_testCase * ACUTE_createTestCase (unsigned char * testCaseName) {
	ACUTE_testCase * newTestCase = (ACUTE_testCase *) malloc (sizeof (ACUTE_testCase));

	if (newTestCase == NULL || testCaseName == NULL) {
		ACUTE_Throw (ACUTE_MEMORY_EXCEPTION);
	} else {
		newTestCase->testCaseName = testCaseName;
		newTestCase->testCaseHead = NULL;
		newTestCase->testSetup = NULL;
		newTestCase->testTearDown = NULL;

		ACUTE_queueTestCase (newTestCase);
	}

	return newTestCase;
}


/*
 * FUNCTION: ACUTE_createSetup
 * ------------------------------------------------------
 * Queues Test Method at the end of the Test Case linked list
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
void ACUTE_createSetup (ACUTE_testCase * testCase, unsigned char * setupMethodName, void (*setupMethod) (void)) {
	if (testCase == NULL) {

	} else {
		testCase->testSetup = setupMethod;
	}
}


/*
 * FUNCTION: ACUTE_createTearDown
 * ------------------------------------------------------
 * Queues Test Method at the end of the Test Case linked list
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
void ACUTE_createTearDown (ACUTE_testCase * testCase, unsigned char * tearDownName, void (*tearDownMethod) (void)) {
	testCase->testTearDown = tearDownMethod;
}


/*
 * FUNCTION: ACUTE_createTestMethod
 * ------------------------------------------------------
 * Queues Test Method at the end of the Test Case linked list
 *
 * IN:
 * 	- Newly created Test Method.
 * OUT:
 * 	- N/A
 */
void ACUTE_createTestMethod (ACUTE_testCase * testCase, unsigned char * testMethodName,  void (*testMethod) (void)) {
	ACUTE_testMethod * newTestMethod = (ACUTE_testMethod *) malloc (sizeof (ACUTE_testMethod));

	if (newTestMethod == NULL || testCase == NULL || testMethodName == NULL) {
		ACUTE_Throw (ACUTE_MEMORY_EXCEPTION);
	} else {
		newTestMethod->testCase = testCase;
		newTestMethod->testMethodName = testMethodName;
		newTestMethod->testMethod = testMethod;
		newTestMethod->prevMethod = NULL;
		newTestMethod->nextMethod = NULL;

		ACUTE_queueTestMethod (newTestMethod);
	}
}

