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


/*
 * STRUCTURE DEFINITIONS
 * ======================================================
 */

typedef struct __ACUTE_TEST_METHOD__ {
	unsigned char * testMethodName;
	void (*testMethod) (void);
	struct __ACUTE_TEST_METHOD__ * nextMethod;
	struct __ACUTE_TEST_METHOD__ * prevMethod;
} ACUTE_testMethod;

typedef struct __ACUTE_TEST_CASE__ {
	unsigned char * testCaseName;
	ACUTE_testMethod * testCaseHead;
	ACUTE_testMethod * testSetup;
	ACUTE_testMethod * testTearDown;
} ACUTE_testCase;

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
extern void ACUTE_createTestCase (unsigned char * testCaseName);
extern void ACUTE_insertTestMethod (unsigned char * testMethodName, ACUTE_testCase * testCase, void (*testMethod) (void));

#endif /* ACUTETEST_H_ */
