#ifndef TEST_TRACKER_H
#define TEST_TRACKER_H

// Declaration of test tracking function

void testInternal(_Bool success, int lineNum, char *argStr);

// Declaration of global variables for test tracking
extern int numTests;
extern int numTestsPassed;

#endif // TEST_TRACKER_H
