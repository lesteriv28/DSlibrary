#include "myList.h"

// MYList functions
struct node *List_createNode(int data)
{

	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void List_insertHead(struct node **headRef, struct node *newNode)
{

	if (*headRef == NULL)
	{

		if (newNode == NULL)
		{
			newNode = List_createNode(0);
		}
		*headRef = newNode;
	}
	else
	{

		newNode->next = *headRef;
		*headRef = newNode;
	}
}

void List_insertTail(struct node **headRef, struct node *newNode)
{
	struct node *temp = *headRef;
	if (*headRef == NULL)
	{
		List_insertHead(headRef, newNode);
	}
	else
	{
		int i = List_countNodes(*headRef);
		int iter = 0;
		while (iter < i - 1 && temp->next != NULL)
		{
			temp = temp->next;
			iter++;
		}
		if (newNode == NULL)
		{
			newNode = List_createNode(0);
		}
		temp->next = newNode;
	}
}

int List_countNodes(struct node *head)
{

	int counter = 0;
	for (; head != NULL; head = head->next)
	{
		counter++;
	}
	return counter;
}

struct node *List_findNode(struct node *head, int item)
{
	struct node *iter = head;
	while (iter != NULL && iter->data != item)
	{
		iter = iter->next;
	}
	return iter;
}

void List_deleteNode(struct node **headRef, struct node *deleter) {
    if (*headRef == NULL || deleter == NULL) {
        return;
    }

    while (*headRef == deleter) {
        *headRef = deleter->next;
        free(deleter);
        deleter = *headRef;
        if (deleter == NULL) {
            return; // No more nodes to delete
        }
    }

    struct node *temp = *headRef;
    while (temp != NULL && temp->next != deleter) {
        temp = temp->next;
    }

    if (temp == NULL) {
        return; // Node not found
    }

    temp->next = deleter->next;
    free(deleter);
}


void List_sort(struct node **headRef)
{
	if (headRef == NULL || *headRef == NULL || (*headRef)->next == NULL)
	{
		return; // No need to sort an empty list or a list with a single node
	}

	struct node *i, *j;
	for (i = *headRef; i->next != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (i->data > j->data)
			{
				int temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}

