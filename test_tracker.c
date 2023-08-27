#include "test_tracker.h"
#include <stdio.h>

int numTests = 0;
int numTestsPassed = 0;

// Function to check success/faillure and update counters
void testInternal(_Bool success, int lineNum, char *argStr) {
	numTests++;
	if (success) {
		printf("Test %s\t\t PASSED\n", argStr);
		numTestsPassed++;
	} else {
		printf("ERROR %4d: test on line %d failed: %s\n", numTests, lineNum, argStr);
	}
}
