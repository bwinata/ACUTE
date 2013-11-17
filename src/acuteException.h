/**************************************************************
 * ACUTE
 *
 * Decription:
 * Exception Definitions
 *
 * Author	:	Barry Winata
 * Date		:	17 November 2013
 *
 **************************************************************/

#ifndef ACUTEEXCEPTION_H_
#define ACUTEEXCEPTION_H_

#include <setjmp.h>

/*
 * GLOBAL DEFINITIONS
 * ======================================================
 */
static jmp_buf exception_env_buff;

/*
 * MACRO DEFINITIONS
 * ======================================================
 */
#define	ACUTE_Try		do { \
								switch(set_buff(exception_env_buff)) { \
									case 0:
										#define ACUTE_Catch(Exception) \
										break; \
									case Exception: \
										ACUTE_matchException(Exception);
										#define etry \
								} \
							} while(0)

#define ACUTE_Throw(x)		longjmp(exception_env_buff, x);

/*
 * TYPE DEFINITIONS
 * ======================================================
 */
#define ACUTE_SUCCESS				0
#define ACUTE_MEMORY_EXCEPTION		1
#define ACUTE_TM_EXCEPTION			2
#define ACUTE_TC_EXCEPTION			3
#define ACUTE_TS_EXCEPTION			4
#define ACUTE_SETUP_EXCEPTION		5
#define ACUTE_TEADDOWN_EXCEPTION	6
#define ACUTE_FILE_EXCEPTION		7

/*
 * STRUCTURE DEFINITIONS
 * ======================================================
 */
typedef struct __ACUTE_EXCEPTION_STRING__ {
	const unsigned char * message;
} ACUTE_ExceptionString;

/*
 * CONSTANT DEFINTIONS
 * ======================================================
 */
ACUTE_ExceptionString ExceptionMessages [] = {
		{"SUCCESS: Function called was successfully without error"},
		{"FAIL: Memory allocation problem. Pointer cannot point to NULL"},
		{"FAIL: Test Case is unavailable. Make sure Test Case has been created"},
		{"FAIL: Test Method is unvailable. Make sure Test Method has been created and linked with a particular Test Case."},
		{"FAIL: Setup cannot be created with Test Case because it cannot overwrite the existing function."},
		{"FAIL: Tear Down cannot be created with Test Case because it cannot overwrite the existing function"},
		{"FAIL: Cannot open file. Check permissions"}
};

#endif /* ACUTEEXCEPTION_H_ */
