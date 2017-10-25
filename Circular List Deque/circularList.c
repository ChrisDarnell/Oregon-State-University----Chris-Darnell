//Author: Chris Darnell
//CS-261(400): Assignment 3
//Date: 10/16/16
//Title: circularList.c
//Description: Implementiation of a circular linked list.
//Solution: The circular linked list can be manipulated as needed by starting from the one sentinel.
//If a value deleted, it must be replaced and its placement set by declaring pointers to link front/back of it.
//Loops can search, remove value/links.


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this

	//Allocates the list's sentinel
	list->sentinel = (struct Link*)malloc(sizeof(struct CircularList));
	assert(list->sentinel != 0);

	//The sentinel's next and prev should point to the sentinel itself.
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->sentinel->value = -1;

	//Set size to 0
	list->size = 0;

}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this

	//Creates a link with the given value
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));

	//Creates NULL next and prev pointers
		newLink->next = NULL;
		newLink->prev = NULL;

	//Store value.
		newLink->value = value;

	//Return created link with the given value
		return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this

		//Adds a new link with the given value...
		struct Link * addMe = createLink(value);

		//...after the given link.
		addMe->next = link->next;
		addMe->prev = link;

		//Create pointers to the these locations.
		(addMe->next)->prev = addMe;
		(addMe->prev)->next = addMe;

		//Increment the list size
		list->size++;


}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this

	//Removes the given link from the list...
	link->prev->next = link->next;
	link->next->prev = link->prev;

	//Delete the link, free the link and set pointers to NULL.
	link->next = NULL;
	link->prev = NULL;
	free(link);
	link = NULL;

	//Decrements the list size
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{

	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this

	//Check list is not already empty, while it is not...
	while (!circularListIsEmpty(list)) {

	//...call removeLink to loop through and destroy every link the list.
		struct Link * temp = list->sentinel->next;
		removeLink(list, temp);
	}

	//Free the list pointer.
	free(list->sentinel);
	free(list);

}



/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	//Call addLink after to add new link with given value to front of deque.
	//Value after sentinel will be front.
	addLinkAfter(list, list->sentinel, value);

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this

	//Call addLink after to add new link with given value to back of deque.
	//Value before sentinel will be back.
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this

	//Return value of link at front of deque.
	//Link after sentinel will be front, get value.
	return ((list->sentinel)->next)->value;

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this

	//Return value of link at back of deque.
	//Link before sentinel will be back, get value.
	return ((list->sentinel)->prev)->value;

}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this


	//Call removeLink to remove link at front of deque.
	//Link after sentinel will be front.
	removeLink(list, (list->sentinel)->next);

}


/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this

	//Call removeLink to remove link at back of deque.
	//Link before sentinel will be back.
	removeLink(list, (list->sentinel)->prev);

}


/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this

	//if deque if empty...
	if (list->size == 0) {

	//return 1
			return 1;
		}
	//0 otherwise.
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this


	int size = list->size;
	struct Link * itr = list->sentinel->next;

	printf("The values of the links in the deque from front to back are...");

			//iterate through list.
			while (size) {

						//set signif digit output
						printf("%g, ", itr->value);
						itr = itr->next;

						//Decrement count for front to back.
						size--;
					}
	//New line.
	printf("\n");

}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	//FIXME: you must write this

	//Start at sentinel...
	struct Link * itr = list->sentinel;

	//Loop through size + one for moving into temp...
	for (int i = 0; i < list->size + 1; i++) {

		//Save next in temp.
		struct Link * temp = itr->next;

		//Set next to previous.
		itr->next = itr->prev;

		//Move saved next into previous.
		itr->prev = temp;

		//Move on
		itr = itr->next;
	}

}
