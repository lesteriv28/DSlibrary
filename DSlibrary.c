#include"DSlibrary.h"
#include<stdio.h>
#include<stdlib.h>




//MyString functions
int mystrlen(const char *s){
	
	int count = 0;
	for(; *s != '\0'; s++)
	{
		count++;
	}
	return count;
}

char *mystrcpy(char *dst, const char *src){
	if(src == NULL) {perror("String to be copied from is empty");}
	char* t = dst;
	while(*src != '\0')
	{
		*t = *src;
		t++;
		src++;
	}
	*t = '\0';
	return dst;
}

int mystrcmp(const char *s1, const char *s2){
	if(s1 == NULL || s2 == NULL) {perror("One or both string empty");}
	while(*s1 != '\0'  && *s2 != '\0'){
		if(*s1 < *s2){
			return -1;
		}
		else if (*s1 > *s2){
			return 1;
		}
		s1++;
		s2++;
	}
	if(*s1 == *s2){return 0;}
	if(*s1 == '\0'){return -1;}
	if(*s2 == '\0'){return 1;}
	return 0;
}

char *mystrdup(const char *src){

	char* rv = malloc(sizeof(char) * mystrlen(src));
	if(src == NULL){perror("Empty string input");}
	else{
		rv = mystrcpy(rv,src);
	}
	return rv;
}


//MYList functions
struct node* List_createNode(int data){

struct node* newNode = malloc(sizeof(struct node));
newNode->data = data;
newNode->next = NULL;
return newNode;

}

void List_insertHead(struct node **headRef, struct node *newNode){

	if(*headRef == NULL){

	if(newNode == NULL){List_createNode(newNode->data);}
		*headRef = newNode;
		
	}
	else{
	
		newNode->next = *headRef;
		*headRef = newNode;
	}

}

void List_insertTail(struct node**headRef, struct node *newNode){
	struct node* temp = *headRef;
	if(*headRef == NULL) {List_insertHead(headRef,newNode);}
	else{
		int i = List_countNodes(*headRef);
		int iter = 0;
		while(iter < i && temp->next != NULL){
		  temp = temp->next;
		}
		if(newNode == NULL){List_createNode(newNode->data);}
		temp->next = newNode;	
	}
}

int List_countNodes(struct node* head){

	int counter = 0;
	for(; head != NULL; head = head->next){
		counter++;	
	}
	return counter;
}

struct node* List_findNode(struct node* head, int item){
	struct node* iter = head;
	while(iter != NULL && iter->data != item){
		iter=iter->next;
	}
	return iter;
}

void List_deleteNode(struct node **headRef, struct node *deleter){
	while(List_findNode(*headRef, deleter->data) != NULL){
		if(deleter->next == NULL && *headRef != deleter){
			struct node* i = *headRef;
			for(; i->next != deleter; i = i->next){
			}
			i->next = NULL;
			free(deleter);
			break;
		}
		else if(*headRef == deleter){
			*headRef = deleter->next;
			free(deleter);
			break;
		}
		else{
			struct node* temp = *headRef;
			while(temp->next != deleter){
			    temp = temp->next;
			}
			temp->next = deleter->next;
			free(deleter);
			break;
		}
	}
}

void List_sort(struct node **headRef){
	if(headRef == NULL || *headRef == NULL) { return;}
	struct node* i, *j;
	int temp;
	for(i = *headRef; i->next != NULL; i = i->next){
		for(j = i->next; j != NULL; j = j->next){
			if(i->data > j->data){
			 temp = i->data;
			 i->data = j->data;
			 j->data = temp;
			}
		}
	}
}
