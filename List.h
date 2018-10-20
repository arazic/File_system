/*
 * List.h
 *
 *  Created on: Dec 23, 2017
 *      Author: ise
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

typedef enum {
	SUCCESS,
	FAIL,
	NODE_NOT_FOUND
} Result;

typedef void* Element;

typedef struct Node_t* Node;
typedef struct List_t* List;
typedef void (*freeFunction)(Element);
typedef int (*compareFunction)(Element,Element);
typedef Element (*copyFunction)(Element);
typedef void (*printFunction)(Element);

struct Node_t{
	void *data;
	struct Node_t *next;
};

struct List_t{
 Node head;
 Node current;
 int num_of_elements;
 freeFunction freeFn;
 compareFunction cmpFn;
 copyFunction cpyFn;
 printFunction pntFn;
};

//create new list
List listCreate(freeFunction freeFunc, compareFunction cmpFunc, copyFunction cpyFunc, printFunction printFunc);

//add new node to list
Result listAddNode(List list, void *data);

//add new node to unsorted list
Result listAddNonSorted(List list,void* data);


//search Node
Node listNodeSearch(List list, void* data);//chen-data it's the key for the map!

//search node and return element
Element listNodeSearchElem(List list, void* data);

// delete node
Result listNodeDelete(List list,void* data);

Element listGetFirst(List list);

Element listGetNext(List list);

Element getLastElem(List list);

Element listGetElement(List list,Element e);

Node listGetElementNode(List list,Element e);
//delete list
void listDestroy(List list);

//print all list
void listPrint(List list);


#endif /* LIST_H_ */
