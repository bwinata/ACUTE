#include "acuteException.h"

static void ACUTE_matchException (unsigned int exceptionFlag) {
	printf ("%s\n", ExceptionMessages[exceptionFlag].message);
}
