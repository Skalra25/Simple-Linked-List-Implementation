/*******************************************************************************************
* File Name          : Skalra_Assign1_LinkedListsV2.c
* Description        : Prog8130 - Assignment 1: Linked Lists
*					   This program uses linked lists to hold and print a list of words
*					   organized by index number assosciated with each word. Each word can
*					   consist of maximum 30 characters.
*
* Author:            : Sagal Singh Kalra
* Date:              : 01-10-2021
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS   10					// the number of data items to be used in list

// structure/typedef used for holding data
typedef struct {
	char name[30];
	int index;
} inputData;

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	char   NameData[30];		            // the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex);
void PrintLinkedList(LinkedListNodeDef* ptrHead);


// make the data positions the last 5 digits of student number
// for example if my student number ended in 94330 the data will be as supplied

// data used for test
// paste the data here that was created by Prog8130Assign1DataCreator.exe
// Used the following data in your assignment #1
inputData iData[10] = {
		{ "chocolate", 2 },
		{ "pickels", 1 },
		{ "butter", 2 },
		{ "milk", 1 },
		{ "airplane", 8 },
		{ "orange", 2 },
		{ "water", 8 },
		{ "kiwi", 9 },
		{ "fish", 6 },
		{ "allan", 8 }
};
//end of data for assignment

// Correct order after inserting into list is:
// 1. milk
// 2. orange
// 3. pickels
// 4. butter
// 5. chocolate
// 6. fish
// 7. airplane
// 8. allan
// 9. water
// 10. kiwi


int main(void) {
	int i;

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
		printf("%s , %d\n", iData[i].name, iData[i].index);

	// insert the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index);

	// now print out the list in order it is stored starting at head
	PrintLinkedList(ptrHead);
	return 0;
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex) {
	// put code in here to add the item(s) to the linked list

	LinkedListNodeDef* ptr;          // Node pointer declaration
	LinkedListNodeDef* newNode;      // New Node declaration
	static int dataIndexCount = 0;	 // Counter to count index of inserted item
	
    /* Memory Allocation of newNode
	   Allocation fails if newNode address is NULL */
	newNode = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef));
	if (newNode == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}

	strncpy_s(newNode->NameData, NameData, 30); //Load data element into newNode

	/* If index is 1 or the list is empty then 
	   insertion will occur at top of the list.
	   After insertion data index counter is incremented*/
	if (DataIndex == 1 || ptrHead == NULL) {
		newNode->ptrNextNode = ptrHead;
		ptrHead = newNode;
		dataIndexCount++;
	}

	/* If index is less than index of previous inserted element,
	   then data will be inserted before the node and data index
	   counter will be incremented. */
	else if (DataIndex <= dataIndexCount) {
		ptr = ptrHead;
		for (int i = 1; i < DataIndex-1 ; i++) {
			ptr = ptr->ptrNextNode;
		}
		newNode->ptrNextNode = ptr->ptrNextNode;
		ptr->ptrNextNode = newNode;
		dataIndexCount++;
	}

	/* If index is greater than the previous inserted element,
	   then data will be inserted at the end of the list and 
	   data index counter will be updated. */
	else {
		ptr = ptrHead;
		while (ptr->ptrNextNode != NULL) {
			ptr = ptr->ptrNextNode;
		}
		ptr->ptrNextNode = newNode;
		newNode->ptrNextNode = NULL;
		dataIndexCount++;

	}
	return ptrHead;  // Returns head of the linked list.
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	// put code in here to print the linked list out

	LinkedListNodeDef* ptr;  // Node pointer declaration
	int i = 1;

	/* Check the NULLness of the Head pointer and,
	   List is empty is printed*/
	if (ptrHead == NULL) {
		printf("The List is empty!!\n");
		return;
	}

	ptr = ptrHead;// Node pointer initialization
	printf("\nData after Linked List is:\n\n");

	/* Linked List is traversed using while loop and
	   the list is then printed */
	while (ptr != NULL) {
		printf("%d.%s\n", i,ptr->NameData);
		ptr = ptr->ptrNextNode;
		i++;
	}
}
