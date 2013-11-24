/**************************************************************
 * ACUTE - Another C Unit Testing Environment
 * ------------------------------------------------------------
 * Decription:
 * 	Execution framework responsible for verifying validity of
 * 	Test Cases / Methods and proceeds to run Unit Tests. Generates
 * 	output summary on the command line.
 *
 * Module	:	ACUTE Framework
 * File		:	acuteFramework.h
 *
 * Author	: 	Barry Winata
 * Date		:	14 November 2013
 * Contact	:	barry.winata@yahoo.com
 *
 **************************************************************/

#ifndef ACUTEFRAMEWORK_H_
#define ACUTEFRAMEWORK_H_

#include <stdlib.h>

/*
 * PUBLIC STRUCTURE DEFINITIONS
 * ======================================================
 */
typedef struct __ACUTE_TEST_METHOD__ ACUTE_testMethod;
typedef struct __ACUTE_TEST_CASE__ ACUTE_testCase;
typedef struct __ACUTE_TEST_SUITE__ ACUTE_testSuite;

/*
 * GLOBAL DEFINITIONS
 * ======================================================
 */
extern ACUTE_testSuite * globalHeadQueue;

/*
 * PUBLIC FUNCTION DECLARATIONS
 * ======================================================
 */
extern ACUTE_testCase * ACUTE_createTestCase (unsigned char * testCaseName);
extern void ACUTE_createSetup (ACUTE_testCase * testCase, unsigned char * setupMethodName, void (*setupMethod) (void));
extern void ACUTE_createTearDown (ACUTE_testCase * testCase, unsigned char * tearDownName, void (*tearDownMethod) (void));
extern void ACUTE_createTestMethod (ACUTE_testCase * testCase, unsigned char * testMethodName, void (*testMethod) (void));

extern void ACUTE_run (void);

#endif /* ACUTEFRAMEWORK_H_ */
