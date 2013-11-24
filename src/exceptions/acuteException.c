/**************************************************************
 * ACUTE - Another C Unit Testing Environment
 * ------------------------------------------------------------
 * Decription:
 * 	Responsible for exception handling. Exceptions are thrown
 * 	and respectively caught by the "Try / Catch" statement.
 *
 * Module	:	ACUTE Exceptions
 * File		:	acuteException.c
 *
 * Author	: 	Barry Winata
 * Date		:	17 November 2013
 * Contact	:	barry.winata@yahoo.com
 *
 **************************************************************/

#include "acuteException.h"

static void ACUTE_matchException (unsigned int exceptionFlag) {
	printf ("%s\n", ExceptionMessages[exceptionFlag].message);
}
