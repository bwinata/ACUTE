#include "acuteTest.h"

ACUTE_testSuite * globalHeadQueue = NULL;

/*
 * PRIVATE FUNCTIONS DEFINITIONS
 * ======================================================
 */
static void ACUTE_insertTestCase (ACUTE_testCase * testCase) {
	ACUTE_testCase * tempCase = globalHeadQueue;

}

static ACUTE_testSuite * ACUTE_createTestQueue (ACUTE_testCase * testCase) {
	ACUTE_testSuite * queue = (ACUTE_testSuite *) malloc (sizeof (ACUTE_testSuite));

	queue->testSuiteName = "General Test Case Queue";
	queue->testCase = testCase;
	queue->next = NULL;
	queue->prev = NULL;

	return queue;
}

static void ACUTE_queueTestCase (ACUTE_testCase * testCase) {
	if (globalHeadQueue == NULL) {
		globalHeadQueue = ACUTE_createTestQueue (testCase);
	}
}

/*
 * PUBLIC FUNCTIONS DEFINITIONS
 * ======================================================
 */
void ACUTE_createTestCase (unsigned char * testCaseName) {
	ACUTE_testCase * newTestCase = (ACUTE_testCase *) malloc (sizeof (ACUTE_testCase));

	newTestCase->testCaseName = testCaseName;
	newTestCase->testCaseHead = NULL;
	newTestCase->testSetup = NULL;
	newTestCase->testTearDown = NULL;

	ACUTE_queueTestCase (newTestCase);

	//globalHeadSuite == NULL ? (globalHeadSuite = newTestCase) : ACUTE_queueTestCase (newTestCase);
}


