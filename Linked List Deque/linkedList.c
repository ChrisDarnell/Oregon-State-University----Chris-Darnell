//Author: Chris Darnell
//CS-261(400): Assignment 3
//Date: 10/16/16
//Title: linkedList.c
//Description: Implementiation of a linked list.
//Solution: The linked list can be manipulated as needed by starting from either sentinel, front or back.
//If a value deleted, it must be replaced and its placement set by declaring pointers to link front/back of it, by ref of sentinels.
//Loops can search, remove value/links.



#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {

	// FIXME: you must write this

	//Allocates the lists' sentinel, front...
	struct Link * front = (struct Link*)malloc(sizeof(struct Link));
	assert(front != 0);

	//...back
	struct Link * back = (struct Link*)malloc(sizeof(struct Link));
	assert(back != 0);

	//The sentinels' next and prev should point to eachother or NULL
	front->prev = back;
	front->next = NULL;

	back->prev = NULL;
	back->next = front;

	//Reassign.
	list->frontSentinel = front;
	list->backSentinel = back;

	//Sets the list size to 0
	list->size = 0;

}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
// static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
// {
// 	// FIXME: you must write this
//
//
// 		//Create new link to add.
// 		struct Link * newLink = (struct Link*)malloc(sizeof(struct Link));
//
// 		//Save link 'before.'
// 		struct Link * behindNewLink;
// 		behindNewLink = link->prev;
//
// 		//Pointers to link location.
// 		link->prev = newLink;
// 		behindNewLink->next = newLink;
//
// 		//Set location.
// 		newLink->prev = behindNewLink;
// 		newLink->next = link;
//
// 		//Place value.
// 		newLink->value = value;
//
// 		//Increment the list size
// 		list->size++;
//
// 	}
//
// /**
//  * Removes the given link from the list and
//  * decrements the list's size.
//  */
// static void removeLink(struct LinkedList* list, struct Link* link)
// {
// 	// FIXME: you must write this
//
// 	//Check there is something to remove.
// 	assert(list->size != 0);
//
// 	//Create pointers for link, before and after.
// 	struct Link * deleteMe = link;
// 	struct Link * beforeDeleteMe = link->prev;
// 	struct Link * afterDeleteMe = link->next;
//
// 	//Pointer assignment.
// 	beforeDeleteMe->next = afterDeleteMe;
// 	afterDeleteMe->prev = beforeDeleteMe;
//
// 	//Delete link, free pointer
// 	deleteMe->next = NULL;
// 	deleteMe->prev = NULL;
// 	free(deleteMe);
//
// 	//Decrement the list size
// 	list->size--;
// }

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

		//Adds a new link with the given value...
		struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
		struct Link * prevFront;
		prevFront = (list->frontSentinel)->prev;

		//...to the front of the deque.
		prevFront->next = newLink;
		(list->frontSentinel)->prev = newLink;

		//Assign location pointers.
		newLink->next = list->frontSentinel;
		newLink->prev = prevFront;

		//Assign value.
		newLink->value = value;

		//Increment the size
		list->size++;

	}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Add a new link with the given value...
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	struct Link * prevBack;
	prevBack = (list->backSentinel)->next;

	//..to the back of the deck.
	prevBack->prev = newLink;
	(list->backSentinel)->next = newLink;

	//Assign location pointers.
	newLink->prev = list->backSentinel;
	newLink->next = prevBack;

	//Assign value.
	newLink->value = value;

	//Increment the size t
	list->size++;

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this

	assert(list->size != 0);

	//returns the value of link at front of deque
	//value before frontsent
	return list->frontSentinel->prev->value;

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{

	// FIXME: you must write this

	assert(list->size != 0);

	//returns the value of link at back of deque
	//value after backSent
	return list->backSentinel->next->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this


	assert(list->size != 0);

	//Set up structure to delete link..
	struct Link * deleteMe;

	//...and delete link at front.
	deleteMe = list->frontSentinel->prev;

	//Set up structure to replace removed link.
	struct Link * newFront;
	newFront = list->frontSentinel->prev->prev;

	//Reassignn sent/first link.
	newFront->next = list->frontSentinel;
	list->frontSentinel->prev = newFront;

	//Delete link/free
	deleteMe->prev = NULL;
	deleteMe->next = NULL;
	free(deleteMe);
	deleteMe = NULL;

	//Decrement the size from delete
	list->size--;

}
/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this

		assert(list->size != 0);

		//Link at back of deque being deleted.
		struct Link * deleteMe;
		deleteMe = list->backSentinel->next;

		//Link to replace deleted link.
		struct Link * newBack;
		newBack = list->backSentinel->next->next;

		//Reassign.
		newBack->prev = list->backSentinel;
		list->backSentinel->next = newBack;

		//free
		deleteMe->next = NULL;
		deleteMe->prev = NULL;
		free(deleteMe);
		deleteMe = NULL;

		//Decrement the size from delete
		list->size--;

	}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this

	//if size of list is 0...
	if (list->size == 0) {

	//...return one if deque is empty...
		return 1;
		}

	//...and 0 otherwise.
	else {
		return 0;
			}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this


	assert(list->size != 0);
	printf("The values of the links in the deque from front to back are: "),0;

	struct Link * printVal = list->frontSentinel->prev;

	//Loop for output, front to back.
	do {
		printf(" %d ", printVal->value);
		printVal = printVal->prev;

	}

	while (printVal->prev != 0);
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this

	//Call function to add value to back.
	linkedListAddBack(list, value);
}
/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE e)
{
	// FIXME: you must write this

	//if nothing, doesn't contain
	assert(list->size != 0);

 	struct Link * currLink = list->frontSentinel->prev;

	//loop to search, checking value
 			do {

	//Returns 1 if a link with the value is in the bag and...
	 			if (currLink->value == e) {
		 			return 1;
	 				}
	 currLink = currLink->prev;
					}

	//...0 otherwise.
		while (currLink->prev != 0);

 	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this


		//Make sure it's in there.
		assert(list->size != 0);
		assert(linkedListContains(list, value));

		struct Link * currLink = list->frontSentinel->prev;

		//Removes the first occurrence of a link with the given value.
		do {

			if (currLink->value == value) {

				currLink->next->prev = currLink->prev;
				currLink->prev->next = currLink->next;

				currLink->next = NULL;
				currLink->prev = NULL;
				free(currLink);

				//Decrement size from delete.
				list->size--;

				return;
			}
			currLink = currLink->prev;
		}

		while (currLink != 0);
}
