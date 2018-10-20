/*
 * List.c
 *
 *  Created on: Dec 5, 2017
 *      Author: ise
 */


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"


//Create new list
List listCreate(freeFunction freeFunc, compareFunction cmpFunc, copyFunction cpyFunc , printFunction printFunc){
	List list= malloc(sizeof(struct List_t));
	if(!list){
		return NULL;
	}
	list->head=NULL;
	list->current=NULL;
	list->freeFn=freeFunc;
	list->cmpFn=cmpFunc;
	list->cpyFn=cpyFunc;
	list->pntFn=printFunc;
	list->num_of_elements=0;
	return list;
}

//Create new node
Result listAddNode(List list, void *data){
	if (data==NULL){
		return FAIL;
	}
	Node node= malloc(sizeof(struct Node_t));
	if(!node){
	  return FAIL;
	 }
	node->data=list->cpyFn(data);
	list->num_of_elements++;
	if(list->head==NULL){
		list->head=node;
		list->head->next=NULL;
		return SUCCESS;
	}

	Node prev=NULL;;
	Node current=list->head;
	Node next=list->head->next;
	if(current==NULL){
		list->head=node;
		node->next=NULL;
		return SUCCESS;
	}
	if(next==NULL){
		if(list->cmpFn(list->head->data,node->data)!=1){// if num1>num2 return 1;
			current->next=node;
			node->next=NULL;
			return SUCCESS;
		}
		else{
			node->next=current;
			list->head=node;
			current->next=NULL;
			return SUCCESS;
		}
	}
	while((int)list->cmpFn(current->data,node->data)!=1){
		prev=current;
		current=current->next;
		if(current==NULL){
			prev->next=node;
			node->next=NULL;
			return SUCCESS;
		}
	}
	if(prev==NULL){
		node->next=list->head;
		list->head=node;
		return SUCCESS;

	}
	prev->next=node;
	node->next=current;
	return SUCCESS;
}

Result listAddNonSorted(List list,void* data){
	if (data==NULL){
		return FAIL;
	}
	Node node= malloc(sizeof(struct Node_t));
	if(!node){
	  return FAIL;
	 }
	list->num_of_elements++;
	node->data=list->cpyFn(data);
	if(list->head==NULL){
		list->head=node;
		list->head->next=NULL;
	}
	else{
		list->current=list->head;
		list->head=node;
		list->head->next=list->current;
	}
	return SUCCESS;
}

//search node
Node listNodeSearch(List list, void* data){//Element
	Node ptr=list->head;
	if (list==NULL || data==NULL){
		return NULL;
	}
	while(ptr!=NULL){
			if(list->cmpFn(data,ptr->data)==0){
				return ptr;//ptr-data
			}
		ptr=ptr->next;
	}
	return NULL;
}

Element listNodeSearchElem(List list, void* data){
	Node ptr=list->head;
	if (list==NULL || data==NULL){
		return NULL;
	}
	while(ptr!=NULL){
			if(list->cmpFn(data,ptr->data)==0){
				return ptr->data;
			}
		ptr=ptr->next;
	}
	return NULL;
}

Element listGetElement(List list,Element e){
	Node ptr=list->head;
		if (list==NULL || e==NULL){
			return NULL;
		}
		while(ptr!=NULL){
				if((list->cmpFn(e,ptr->data))==0){
					return ptr->data;//ptr-data
				}
			ptr=ptr->next;
		}
		return NULL;
}

Node listGetElementNode(List list,Element e){
	Node ptr=list->head;
			if (list==NULL || e==NULL){
				return NULL;
			}
			while(ptr!=NULL){
					if((list->cmpFn(e,ptr->data))==0){
						return ptr;//ptr-data
					}
				ptr=ptr->next;
			}
			return NULL;
}
Result listNodeDelete(List list,void* data){
	if(list==NULL||data==NULL){
		return FAIL;
	}
	Node node=listNodeSearch(list,data);
	if(node==NULL)
		return FAIL;
	list->num_of_elements--;
	if(node==list->head){
		list->head=list->head->next;
		list->freeFn(node->data);
		free(node);
		return SUCCESS;
	}
	Node curr=list->head;
	Node prev=NULL;
	while(curr!=node){
		prev=curr;
		curr=curr->next;
	}
	if(prev)
		prev->next=curr->next;
	list->freeFn(node->data);
	free(node);
	return SUCCESS;
}

void listDestroy(List list){
	while((list->head)!=NULL){
		listNodeDelete(list,list->head->data);
	}
}

void listPrint(List list){
	if(list==NULL){
		printf("your list is empty");
	}
	Node ptr=list->head;
	while(ptr!=NULL){
		list->pntFn(ptr->data);
		ptr=ptr->next;
	}

}

Element listGetFirst(List list){
	if(list==NULL)
		return NULL;
	list->current=list->head;
	if(list->current==NULL)
		return NULL;
	return list->current->data;
}

Element listGetNext(List list){
	list->current=list->current->next;
	if(list->current!=NULL)
		return list->current->data;
	return NULL;
}

Element getLastElem(List list){
	if(!list|!list->head)
		return NULL;
	Node n=list->head;
	while (n->next!=NULL){
		n=n->next;
	}
	return n->data;
}

