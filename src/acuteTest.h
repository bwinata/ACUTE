/**************************************************************
 * ACUTE
 *
 * Decription:
 * Test Method Defintions
 *
 * Author	: 	Barry Winata
 * Date		:	14 November 2013
 *
 **************************************************************/

#ifndef ACUTETEST_H_
#define ACUTETEST_H_

#include <stdlib.h>

/*
 * TYPE DEFINITIONS
 * ======================================================
 */
#define GENERAL_TEST_QUEUE_NAME		"General Test Case Queue"

/*
 * STRUCTURE DEFINITIONS
 * ======================================================
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
 * PUBLIC FUNCTION DECLARATIONS
 * ======================================================
 */
extern ACUTE_testCase * ACUTE_createTestCase (unsigned char * testCaseName);
extern void ACUTE_createSetup (ACUTE_testCase * testCase, unsigned char * setupMethodName, void (*setupMethod) (void));
extern void ACUTE_createTearDown (ACUTE_testCase * testCase, unsigned char * tearDownName, void (*tearDownMethod) (void));
extern void ACUTE_createTestMethod (ACUTE_testCase * testCase, unsigned char * testMethodName, void (*testMethod) (void));

#endif /* ACUTETEST_H_ */
