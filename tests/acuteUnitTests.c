#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	printf ("======================================\n");
	printf ("ACUTE Unit Tests\n");
	printf ("======================================\n");

	printf ("--------------------------------------\n");
	printf ("Unit Test: ACUTE_unitTest__createTestCase\n");
	ACUTE_unitTest__createTestCase ();
	printf ("--------------------------------------\n");
	printf ("Unit Test: ACUTE_unitTest__createTestMethod\n");
	ACUTE_unitTest__createTestMethod ();
	printf ("--------------------------------------\n");
	printf ("Unit Test: ACUTE_unitTest__insertTestMethodIntoQueue\n");
	ACUTE_unitTest__insertTestMethodIntoQueue ();
	printf ("--------------------------------------\n");
	printf ("Unit Test: ACUTE_unitTest__insertTestQueueIntoQueue\n");
	ACUTE_unitTest__insertTestCaseIntoQueue ();
	printf ("--------------------------------------\n");
	return 0;
}
