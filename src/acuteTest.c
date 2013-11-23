#include "acuteTest.h"
#include "acuteAsserts.h"

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
 * file.
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
ACUTE_testSuite * globalHeadQueue = NULL;

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
	ACUTE_testSuite * tempSuitePrev = NULL;
	while (tempSuite != NULL) {
		tempSuitePrev = tempSuite;
		tempSuite = tempSuite->next;
	}
	tempSuitePrev->next = testSuite;
	testSuite->prev = tempSuitePrev;
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
	ACUTE_testMethod * tempMethodPrev = NULL;

	while (tempMethod != NULL) {
		tempMethodPrev = tempMethod;
		tempMethod = tempMethod->nextMethod;
	}
	tempMethodPrev->nextMethod = testMethod;
	testMethod->prevMethod = tempMethodPrev;
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

	newTestCase->testCaseName = testCaseName;
	newTestCase->testCaseHead = NULL;
	newTestCase->testSetup = NULL;
	newTestCase->testTearDown = NULL;

	ACUTE_queueTestCase (newTestCase);

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

	if (testCase == NULL) {
		printf ("Cannot create Test Method. Test Case is invalid!...Exiting\n");
		exit (1);
	}
	newTestMethod->testCase = testCase;
	newTestMethod->testMethodName = testMethodName;
	newTestMethod->testMethod = testMethod;
	newTestMethod->prevMethod = NULL;
	newTestMethod->nextMethod = NULL;

	ACUTE_queueTestMethod (newTestMethod);
}


/*
 * UNIT TESTS
 * ======================================================
 */

/*
 * FUNCTION: ACUTE_unitTest__insertTestMethodIntoQueue
 * ------------------------------------------------------
 * Inserts a Test Method into an existing queue and verifies
 * that the Test Method / Test Case is valid as well as the queue.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_unitTest__insertTestMethodIntoQueue (void) {
	/* Create Test Methods and allocate memory */
	ACUTE_testMethod * testMethod = (ACUTE_testMethod *) malloc (sizeof(ACUTE_testMethod));
	ACUTE_testMethod * anotherTestMethod = (ACUTE_testMethod *) malloc (sizeof(ACUTE_testMethod));
	/* Create Test Case and allocate memory */
	ACUTE_testCase * testCase = (ACUTE_testCase *) malloc (sizeof(ACUTE_testCase));

	/* Check if memory has been allocated properly to test entities */
	ACUTE_ASSERT_NOT_NULL (testMethod);
	ACUTE_ASSERT_NOT_NULL (anotherTestMethod);
	ACUTE_ASSERT_NOT_NULL (testCase);

	/* Check if prev / next pointers are NULL */
	ACUTE_ASSERT_NULL (testMethod->nextMethod);
	ACUTE_ASSERT_NULL (testMethod->prevMethod);
	ACUTE_ASSERT_NULL (anotherTestMethod->nextMethod);
	ACUTE_ASSERT_NULL (anotherTestMethod->prevMethod);

	/* Link Test Method to Test Case Head */
	testCase->testCaseHead = testMethod;
	/* Link Test Case to Test Method */
	testMethod->testCase = testCase;
	anotherTestMethod->testCase = testCase;

	/* Check if Test Case has been allocated to Test Method */
	ACUTE_ASSERT_NOT_NULL (testMethod->testCase);
	/* Check if Test Case head has been allocated to Test Method */
	ACUTE_ASSERT_NOT_NULL (testMethod->testCase->testCaseHead);
	ACUTE_ASSERT_NOT_NULL (anotherTestMethod->testCase->testCaseHead);

	/* Check if Test Cases are the same for both Test Methods */
	ACUTE_ASSERT_EQUAL (testMethod->testCase, anotherTestMethod->testCase);

	/* Insert Method into queue */
	ACUTE_insertTestMethodIntoQueue (anotherTestMethod);

	/* Check that the new method has been appended to queue */
	ACUTE_ASSERT_NOT_NULL(anotherTestMethod->prevMethod);
	ACUTE_ASSERT_NULL(anotherTestMethod->nextMethod);
}

/*
 * FUNCTION: ACUTE_unitTest__insertTestMethodIntoQueue
 * ------------------------------------------------------
 * Inserts a two Test Cases into a queue in order to verify
 * that the test cases are valid and ensuring the global head queue
 * is properly created.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_unitTest__insertTestCaseIntoQueue (void) {
	/* Create and allocate memory for two Test Suites to be queued */
	ACUTE_testSuite * testSuite = (ACUTE_testSuite *) malloc (sizeof (ACUTE_testSuite));
	ACUTE_testSuite * anotherTestSuite = (ACUTE_testSuite *) malloc (sizeof (ACUTE_testSuite));

	/* Check each Test Suite is not NULL */
	ACUTE_ASSERT_NOT_NULL (testSuite);
	ACUTE_ASSERT_NOT_NULL (anotherTestSuite);

	/* Check that global head queue is NULL */
	globalHeadQueue = NULL;
	ACUTE_ASSERT_NULL (globalHeadQueue);

	/* Assign first Test Suite as Head of queue */
	globalHeadQueue = testSuite;
	/* Check that Global Head queue is not NULL */
	ACUTE_ASSERT_NOT_NULL (globalHeadQueue);

	/* Queue Test Case */
	ACUTE_insertTestCaseIntoQueue (anotherTestSuite);

	/* Check that new Test Suite is correctly positioned in queue */
	ACUTE_ASSERT_NOT_NULL (anotherTestSuite->prev);
	ACUTE_ASSERT_NULL (anotherTestSuite->next);
}

/*
 * FUNCTION: ACUTE_testMethodDummy
 * ------------------------------------------------------
 * Test Method to be allocated to Test Case.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_testMethodDummy (void) {
	printf ("This is a test method\n");
}

/*
 * FUNCTION: ACUTE_unitTest__createTestCase
 * ------------------------------------------------------
 * Creates a Test Case. Test ensures that the Global Head
 * is NULL, the proceeds to insert Cases. Finally checks that
 * Cases are properly positioned in the queue.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_unitTest__createTestCase (void) {
	/* Set Global Head to NULL */
	globalHeadQueue = NULL;
	/* Check that Global Head is NULL */
	ACUTE_ASSERT_NULL (globalHeadQueue);

	/* Create Test Case */
	ACUTE_createTestCase ("Test Case 1");
	ACUTE_createTestCase ("Test Case 2");

	/* Check that Global Head is not NULL because a new Test Suite / Test Case has been created */
	ACUTE_ASSERT_NOT_NULL (globalHeadQueue);
	/* Check that the Global Head is pointing to the next Test Suite with the next Test Case */
	ACUTE_ASSERT_NOT_NULL (globalHeadQueue->next);

	/* Verify "Test Case 1 / 2" is correctly positioned in queue */
	printf ("%s\n", globalHeadQueue->testCase->testCaseName);
	printf ("%s\n", globalHeadQueue->next->testCase->testCaseName);

}

/*
 * FUNCTION: ACUTE_unitTest__createTestMethod
 * ------------------------------------------------------
 * Creates a Test Method and appends it to the queue. Checks
 * that Test can be executed correctly from the queue.
 *
 * IN:
 * 	- N/A
 * OUT:
 * 	- N/A
 */
void ACUTE_unitTest__createTestMethod (void) {
	/* Create and allocate memory for a Test Case */
	ACUTE_testCase * testCase = (ACUTE_testCase *) malloc (sizeof (ACUTE_testCase));

	/* Check Test Case is not NULL */
	ACUTE_ASSERT_NOT_NULL (testCase);
	/* Check that Test Case head is NULL */
	ACUTE_ASSERT_NULL (testCase->testCaseHead);

	/* Create Test Method */
	ACUTE_createTestMethod (testCase, "Test Method 1", ACUTE_testMethodDummy);

	/* Check Test Method has been appropriately queued */
	ACUTE_ASSERT_NOT_NULL (testCase->testCaseHead);

	/* Run Test Method Dummy */
	testCase->testCaseHead->testMethod ();
}


