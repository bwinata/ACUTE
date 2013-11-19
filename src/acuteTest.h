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
 * PUBLIC TYPE DEFINITIONS
 * ======================================================
 */

/*
 * PUBLIC STRUCTURE DEFINITIONS
 * ======================================================
 */
typedef struct __ACUTE_TEST_METHOD__ ACUTE_testMethod;
typedef struct __ACUTE_TEST_CASE__ ACUTE_testCase;
typedef struct __ACUTE_TEST_SUITE__ ACUTE_testSuite;

/*
 * PUBLIC FUNCTION DECLARATIONS
 * ======================================================
 */
extern ACUTE_testCase * ACUTE_createTestCase (unsigned char * testCaseName);
extern void ACUTE_createSetup (ACUTE_testCase * testCase, unsigned char * setupMethodName, void (*setupMethod) (void));
extern void ACUTE_createTearDown (ACUTE_testCase * testCase, unsigned char * tearDownName, void (*tearDownMethod) (void));
extern void ACUTE_createTestMethod (ACUTE_testCase * testCase, unsigned char * testMethodName, void (*testMethod) (void));

#endif /* ACUTETEST_H_ */
