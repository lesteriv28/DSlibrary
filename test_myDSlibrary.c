#include "DSlibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include "test_functions.h"
#include "test_tracker.h"

int main(){
	// Run tests for string manipulation functions
	printf("Testing String Functions:\n");
	testMyStrLen();
	testMyStrCpy();
	testMyStrCmp();
	testMyStrDup();
	printf("\n");

	// Run tests for linked list operations
	printf("Testing Linked List Operations:\n");
	testInsertAtHead();
	testInsertAtTail();
	testAddManyToHeadOrTail(1);
	testAddManyToHeadOrTail(0);
	testSort();
	printf("\nTesting Summary:\n");
    	printf("%d/%d tests passed.\n", numTestsPassed, numTests);
    	printf("%d/%d tests failed.\n", numTests - numTestsPassed, numTests);
    
    	printf("Execution finished.\n");
	return 0;
	}	
