#ifndef MYLIST_H
#define MYLIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//MyList

//Structs
struct node {
	int data;
	struct node *next;
};

//Allocate memory for a node.
struct node* List_createNode(int data);

//Insert node at the head of the list.
void List_insertHead(struct node **headRef, struct node *Newnode);

//Insert node after the tail of the list.
void List_insertTail(struct node** headRef, struct node *Newnode);

//Count number of nodes in the list
//Return 0 if the list is empty
int List_countNodes(struct node *head);

//Return the first node holding the value item, return NULL if none
struct node* List_findNode(struct node *head, int item);

//Delete node from the list and free memory allocated to it.
//This function assumes that node has been properly set to a valid node
void List_deleteNode(struct node **headRef, struct node *deleter);

//sort the list in ascending order based on the item
void List_sort(struct node **headRef);

#endif