#include "DSlibrary.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "test_functions.h"
#include "test_tracker.h"

/*
 * Custom testing framework
 */
// Track results:

// Macro to allow us to get the line number, and argument's text:
#define TEST(arg) testInternal((arg), __LINE__, #arg)


/*
 * Prototypes
 */
void dumpList(struct node *head);
void addNodes0ToN(struct node **headRef, int n, _Bool atHead);
void printResults(char *title);

#define TERMINATOR -42
void testListSortFromArray(int data[]);
void testInsertAtHead();
void testInsertAtTail();
void testAddManyToHeadOrTail(_Bool addToHead);
void testSort();



/*
 * Helper Functions
 */
void dumpList(struct node *head) {
  struct node *current = head;
  while (current != NULL) {
    printf("%5d", current->data);
    current = current->next;
  }
  printf("\n");
}

void addNodes0ToN(struct node **headRef, int n, _Bool atHead) {
  int initialCount = List_countNodes(*headRef);
  for (int count = 0; count <= n; count++) {
    struct node *node = List_createNode(count);
    if (atHead) {
      List_insertHead(headRef, node);
    } else {
      List_insertTail(headRef, node);
    }
    TEST(List_countNodes(*headRef) == count + initialCount + 1);
    free(node); //Freeing node
  }
  
}

void printResults(char *title) {
  static int testsOnLastPass = 0;
  int testsSinceLast = numTests - testsOnLastPass;
  testsOnLastPass = numTests;

  printf("%s", title);
  printf("%4d/%d tests passed.\n", numTestsPassed, numTests);
  printf("%4d/%d tests FAILED.\n", numTests - numTestsPassed, numTests);
  printf("   (%d tests done since last summary.)\n", testsSinceLast);
  printf("\n");
}

/*
 * Testing Functions
 */

void testInsertAtHead() {
  printf("Adding to head of empty list:\n");
  struct node *list = NULL;

  struct node *firstNode = List_createNode(0);
  TEST(List_countNodes(list) == 0);
  List_insertHead(&list, firstNode);
  TEST(List_countNodes(list) == 1);
  TEST(List_findNode(list, 0) == firstNode);
  TEST(List_findNode(list, 1) == NULL);
  List_deleteNode(&list, firstNode);
  TEST(List_countNodes(list) == 0);
  TEST(List_findNode(list, 0) == NULL);
  TEST(List_findNode(list, 1) == NULL);
}

void testInsertAtTail() {
  printf("Adding to tail of empty list:\n");
  struct node *list = NULL;

  struct node *secondNode = List_createNode(1);
  TEST(List_countNodes(list) == 0);
  List_insertTail(&list, secondNode);
  TEST(List_countNodes(list) == 1);
  TEST(List_findNode(list, 0) == NULL);
  TEST(List_findNode(list, 1) == secondNode);
  List_deleteNode(&list, secondNode);
  TEST(List_countNodes(list) == 0);
  TEST(List_findNode(list, 0) == NULL);
  TEST(List_findNode(list, 1) == NULL);
}

void testAddManyToHeadOrTail(_Bool addToHead) {
  printf("Adding numbers 0 to 5 at head:\n");
  struct node *list = NULL;
  addNodes0ToN(&list, 5, addToHead);
  TEST(List_countNodes(list) == 6);
  TEST(List_findNode(list, 0)->data == 0);
  TEST(List_findNode(list, 1)->data == 1);
  TEST(List_findNode(list, 2)->data == 2);
  TEST(List_findNode(list, 3)->data == 3);
  TEST(List_findNode(list, 4)->data == 4);
  TEST(List_findNode(list, 5)->data == 5);
}

void testSort() {
  printf("Sorting:\n");
  testListSortFromArray((int[]){TERMINATOR});
  testListSortFromArray((int[]){1, TERMINATOR});
  testListSortFromArray((int[]){1, 2, TERMINATOR});
  testListSortFromArray((int[]){2, 1, TERMINATOR});
  testListSortFromArray((int[]){2, 1, 4, TERMINATOR});
  testListSortFromArray((int[]){1, 3, 4, TERMINATOR});
  testListSortFromArray((int[]){4, 3, 1, TERMINATOR});
  testListSortFromArray((int[]){4, 1, 3, TERMINATOR});
  testListSortFromArray((int[]){2, 4, 6, 3, 1, TERMINATOR});
  testListSortFromArray((int[]){-1, 0, 1, 2, 3, TERMINATOR});
  testListSortFromArray((int[]){5, 4, 3, 2, 1, 0, -1, -2, -3, -4, TERMINATOR});
  testListSortFromArray((int[]){0, 1, 9, 1, -5, 22, 10, 0, -15, TERMINATOR});
}

void testListSortFromArray(int data[]) {
  struct node *list = NULL;

  // Stuff data in:
  for (int i = 0; data[i] != TERMINATOR; i++) {
    struct node *node = List_createNode(data[i]);
    List_insertTail(&list, node);
  }

  // Sort:
  //  printf("List before (then after) sort:\n");
  //  dumpList(list);
  List_sort(&list);
  //  dumpList(list);

  // Check in sorted order:
  struct node *current = list;
  while (current && current->next != NULL) {
    TEST(current->data <= current->next->data);
    current = current->next;
  }

  // Clear
  while (List_countNodes(list)) {
    List_deleteNode(&list, list);
  }
}
