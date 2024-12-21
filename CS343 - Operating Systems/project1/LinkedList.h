#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


typedef int TYPE; // type of Node data

typedef struct DoubleNode
{
	TYPE data;
	int frequency; //frequency of data
	struct DoubleNode *next;
	struct DoubleNode *prev;
} DoubleNode;

typedef struct DoubleList
{
	DoubleNode *head;
	DoubleNode *tail;
    	DoubleNode *current;
    	int size;
} DoubleList;

void resetIterator(DoubleList* List);
DoubleNode* iterate(DoubleList* List);
void insertDataAndFrequency(DoubleList *List, TYPE data, int frequency);

//Given an array of List pointers
DoubleList* mergeLists(DoubleList** Lists, int size){
    DoubleList* mergedList = (DoubleList *)malloc(sizeof(DoubleList));
    mergedList->head = NULL;
    mergedList->tail = NULL;    
    mergedList->current = NULL;

    for (int i = 0; i < size; i++){
        DoubleNode* curElem = iterate(Lists[i]);

        while (curElem != NULL){
            insertDataAndFrequency(mergedList, curElem->data, curElem->frequency);
            curElem = iterate(Lists[i]);
        }
    }
    
    return mergedList;
}

//only get data
char* getListString(DoubleList* List){
	int listSize = List->size;
	int maxDigits = snprintf(NULL, 0, "%d", INT_MAX);
	char* res = malloc((maxDigits+1)*listSize +1); //+1 for /0?.. I think
							   //INT_MAX + 1 bc /n on each line
	res[0] = '\0';//init with empty string

	DoubleNode* curElem = iterate(List);


	
	char* temp = malloc(maxDigits + 2);
	while (curElem != NULL){
		sprintf(temp, "%d\n", curElem->data);
		strcat(res, temp);
		curElem = iterate(List);
	}
	free(temp);
	
	resetIterator(List);
	return res;
}

void printList(DoubleList List)
{
	if (List.head != NULL)
	{
		DoubleNode *cur = (List.head)->next; // if there's a head it's guaranteed there is at least one non-head/non-tail node

		while (cur->next != NULL)
		{
			printf("Number: %d frequency: %d\n", cur->data, cur->frequency);
			cur = cur->next;
		}
	}
	else{
		printf("List is empty");
	}
}

DoubleNode* iterate(DoubleList* List){
    if (List->current == NULL){
        return NULL; //empty list
    }
    //Iterate by one
    List->current = (List->current)->next;
    if (List->current == List->tail){//End of list
        return NULL;
    }
    else{
        return List->current;
    }
}
void resetIterator(DoubleList* List){
    List->current = List->head;
}

DoubleNode *findPrevNode(DoubleList *List, DoubleNode *Node)
{
	DoubleNode *cur = List->head;

	while ((cur->next) && (cur->next)->data <= Node->data)
	{
		cur = cur->next;
	}

	DoubleNode *prev = NULL;

	if (cur->next == NULL)
	{ // tail reached
		prev = cur->prev;
	}
	else
	{
		prev = cur;
	}

	return prev;
}

void insertDataAndFrequency(DoubleList *List, TYPE data, int frequency){

    //If head is null freq should be 0 

    //if findPrevNode returns a node s.t. node->data = data, add to that node's frequency. Else, add a data node

    //Inserted node
	DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
	newNode->data = data;
    newNode->frequency = frequency;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (List->head == NULL){
		List->head = (DoubleNode *)malloc(sizeof(DoubleNode));
		List->tail = (DoubleNode *)malloc(sizeof(DoubleNode));
        List->current = List->head;

		(List->head)->prev = NULL;
		(List->head)->next = newNode;
		(List->tail)->next = NULL;
		(List->tail)->prev = newNode;

		newNode->next = List->tail;
		newNode->prev = List->head;
		List-> size = 1;
	} else {
		DoubleNode *prevNode = findPrevNode(List, newNode);

		//Case 1: prevNode->data == data
		if (prevNode->data == data){
		    prevNode->frequency += frequency;
		    //dealloc newNode since it's not used
		    free(newNode);
		} else { //Case 2: first time adding this number
		    DoubleNode *nextNode = prevNode->next;

		    prevNode->next = newNode;
		    newNode->prev = prevNode;
		    nextNode->prev = newNode;
		    newNode->next = nextNode;

		    prevNode->next = newNode;
		    nextNode->prev = newNode;
		    List->size += 1;
		}
	}
}


void clean(DoubleList *List)
{
	DoubleNode *cur = List->head;

	while (cur != NULL)
	{
		DoubleNode *toBeDeleted = cur;
		cur = cur->next;
		free(toBeDeleted);
	}

	List->head = NULL;
	List->tail = NULL;
}
