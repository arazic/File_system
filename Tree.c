/*
 * Tree.c
 *
 *  Created on: Dec 23, 2017
 *      Author: ise
 */

#include "Tree.h"
#include "List.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "FolFil.h"

struct nodeTree_t{
	void* data;//int
	List listInNode;//list
	freeFunction freeFn;
	compareFunction cmpFn;
	copyFunction cpyFn;
	printFunction pntFn;
};

struct Tree_t{
	List listNode;
	freeFunction freeFn;
	compareFunction cmpFn;
	copyFunction cpyFn;
	printFunction pntFn;
};

int compareTreeNode(void* elem1,void* elem2){
	struct nodeTree_t* n1=(struct nodeTree_t*)elem1;
	struct nodeTree_t* n2=(struct nodeTree_t*)elem2;
//	int a=-1;
	return (int)n1->cmpFn(n1->data, n2->data);
//	return -1;
}

void deleteStructElem(void* elem){
	struct nodeTree_t* node=(struct nodeTree_t*)elem;
	node->freeFn(node->data);
	listDestroy(node->listInNode);
	free(node);
}

//print the struct nodeTreeElement
void printNodeTree(void* elem){
	struct nodeTree_t* n1=(struct nodeTree_t*)elem;
	n1->pntFn(n1->data);
	//listPrint(n1->listInNode);
}


Element copyTreeNode(void* elem){
	if(elem==NULL){
		return NULL;
	}
	struct nodeTree_t* structTreeElem=(struct nodeTree_t*)elem;
	structTreeElement nodeTreeCopy=malloc(sizeof(struct nodeTree_t));
	if(!nodeTreeCopy)
		return NULL;
	nodeTreeCopy->data=structTreeElem->cpyFn(structTreeElem->data);
	nodeTreeCopy->cmpFn=structTreeElem->cmpFn;
	nodeTreeCopy->cpyFn=structTreeElem->cpyFn;
	nodeTreeCopy->freeFn=structTreeElem->freeFn;
	nodeTreeCopy->pntFn=structTreeElem->pntFn;
	nodeTreeCopy->listInNode=listCreate(deleteStructElem,compareTreeNode,copyTreeNode,printNodeTree);
	///////copy all of the list to the new one
	structTreeElem=listGetFirst(structTreeElem->listInNode);
	while(structTreeElem!=NULL){
		listAddNode(nodeTreeCopy->listInNode,structTreeElem);
		structTreeElem=listGetNext(structTreeElem->listInNode);
		structTreeElem->listInNode->num_of_elements=nodeTreeCopy->listInNode->num_of_elements;
	}
	return nodeTreeCopy;
}


Tree treeCreate(freeFunction freeFunc, compareFunction cmpFunc, copyFunction cpyFunc , printFunction printFunc){
	Tree tree= malloc(sizeof(struct Tree_t));
	if(!tree){
		return NULL;
	}
	tree->listNode=listCreate(deleteStructElem,compareTreeNode,copyTreeNode,printNodeTree);
	tree->freeFn=freeFunc;
	tree->cmpFn=cmpFunc;
	tree->cpyFn=cpyFunc;
	tree->pntFn=printFunc;
	return tree;
}


structTreeElement nodeTreeCreate(Tree tree,Element elem){
	if (elem==NULL || tree==NULL)
		return NULL;
	structTreeElement nodeTree=malloc(sizeof(struct nodeTree_t));
	if(!nodeTree)
		return NULL;
	nodeTree->listInNode=listCreate(deleteStructElem,compareTreeNode,copyTreeNode,printNodeTree);
	nodeTree->data=tree->cpyFn(elem);
	nodeTree->cmpFn=tree->cmpFn;
	nodeTree->cpyFn=tree->cpyFn;
	nodeTree->freeFn=tree->freeFn;
	nodeTree->pntFn=tree->pntFn;
	return nodeTree;
}



Result Add(Tree tree,Element elem){
	if (tree==NULL|| elem==NULL)
		return FAIL;
	structTreeElement nodeTree=nodeTreeCreate(tree,elem);
	if(nodeTree==NULL){
		return FAIL;
	}
	if(listAddNode(tree->listNode,nodeTree)==SUCCESS){
		deleteStructElem(nodeTree);
		return SUCCESS;
	}
	return FAIL;
}

Result AddIn(Tree t,Element elem,List position){
	struct nodeTree_t* ns=treeSearch(t,position);
	if(ns==NULL)
		return FAIL;
	struct nodeTree_t* new=nodeTreeCreate(t,elem);
	Result r= listAddNode(ns->listInNode,new);
	deleteStructElem(new);
	return r;

}

structTreeElement treeSearch(Tree t, List position){
	Element last=getLastElem(position);
	Element current=(Element)listGetFirst(position);
	struct nodeTree_t* tmp;
	if(last==NULL)
		return NULL;
	List l=t->listNode;
	struct nodeTree_t* st;
	while(t->cmpFn(current,last)!=0){
		tmp=nodeTreeCreate(t,current);
		st=(struct nodeTree_t*)listGetElement(l,tmp);
		deleteStructElem(tmp);
		if(st==NULL){
			return NULL;
		}
		current=listGetNext(position);
		l=st->listInNode;
	}
	tmp=nodeTreeCreate(t,current);
	struct nodeTree_t* retur=(structTreeElement)listGetElement(l,tmp);
	deleteStructElem(tmp);
	return retur;
}

Node treeSearchReturnNode(Tree t, List position){
	Element last=getLastElem(position);
		Element current=(Element)listGetFirst(position);
		List l=t->listNode;
		struct nodeTree_t* tmp;
		struct nodeTree_t* st;
		while(t->cmpFn(current,last)!=0){
			tmp=nodeTreeCreate(t,current);
			st=(struct nodeTree_t*)listGetElement(l,tmp);
			deleteStructElem(tmp);
			if(st==NULL){
				return NULL;
			}
			current=listGetNext(position);
			l=st->listInNode;
		}
		tmp=nodeTreeCreate(t,current);
		Node node=(Node)listGetElementNode(l,tmp);
		deleteStructElem(tmp);
		return node;
}

Result existRoute(Tree t,List position){
	if(treeSearch(t,position)){
		return SUCCESS;
	}
	return FAIL;
}

Element getTreeData(Tree t,List position){
	structTreeElement st=treeSearch(t,position);
	if(!st)
		return NULL;
	return st->data;
}
Result Remove(Tree t, List position){
		Element last=getLastElem(position);
		Element current=(Element)listGetFirst(position);
		List l=t->listNode;
		struct nodeTree_t* tmp;
		tmp=nodeTreeCreate(t,current);
		struct nodeTree_t* st=(struct nodeTree_t*)listGetElement(l,tmp);
		deleteStructElem(tmp);
		if(st==NULL)
			return FAIL;
		while(t->cmpFn(current,last)!=0){
			tmp=nodeTreeCreate(t,current);
			st=(struct nodeTree_t*)listGetElement(l,tmp);
			deleteStructElem(tmp);
			if(st==NULL){
				return FAIL;
			}
			current=listGetNext(position);
			l=st->listInNode;
		}
		tmp=nodeTreeCreate(t,current);
		Result res=listNodeDelete(l,tmp);
		deleteStructElem(tmp);
		return res;
}

Result Reassign(Tree tree,List position,Element contant){
	structTreeElement treeNode=treeSearch(tree, position);
	if(treeNode==NULL){
		return FAIL;
	}
	tree->freeFn(treeNode->data);
	treeNode->data=nodeTreeCreate(tree,contant);
	return SUCCESS;
}

void PrintElem(Node node){
	if(node==NULL){
			return;
		}
	struct nodeTree_t* st=(structTreeElement)node->data;
	printNodeTree(node->data);
	PrintElem(st->listInNode->head);
	char c='\t';
	printf("%c",c);
	PrintElem(node->next);
}

void Print(Tree tree){
	PrintElem(tree->listNode->head);
}

void printNumOfTab(int k){
	char c='\t';
	for(int i=0;i<k;i++){
		printf("%c",c);
	}
}

void printRest(struct nodeTree_t* st,int num_of_tab){
	if(st==NULL)
		return;
	struct t_FolFil* f;
	printNumOfTab(num_of_tab);
	printNodeTree(st);
	f=st->data;
	if(f->Kind==1)
					printf(" %d\n",st->listInNode->num_of_elements);
				else
					printf("\n");
	//printf(" %d\n",st->listInNode->num_of_elements);
	struct nodeTree_t* st_under=listGetFirst(st->listInNode);
	while(st_under!=NULL){
		//printNumOfTab(num_of_tab);
		//printNodeTree(st_under);
		//printf(" %d\n",st_under->listInNode->num_of_elements);
		printRest(st_under,num_of_tab+1);
		st_under=listGetNext(st->listInNode);
	}
}



Result lsPrint(Tree tree,List position,int recursive){
	struct t_FolFil* f;
	if(position==NULL){//print all tree
		struct nodeTree_t* st=listGetFirst(tree->listNode);
		while(st!=NULL){
			printRest(st,0);
			st=listGetNext(tree->listNode);
		}
		return SUCCESS;
	}
	Node treeNode=treeSearchReturnNode(tree, position);
	if(treeNode==NULL)
		return FAIL;

	if(recursive==1){// -r
		struct nodeTree_t* ss=listGetFirst(((struct nodeTree_t*)treeNode->data)->listInNode);
		while(ss!=NULL){
			printRest(ss,0);
			ss=listGetNext(((struct nodeTree_t*)treeNode->data)->listInNode);
		}
	}
	else{
		//print only stuff inside the list. nothing else non recursive
		structTreeElement ss=treeSearch(tree, position);
		structTreeElement st=listGetFirst(ss->listInNode);
		while(st!=NULL){
			tree->pntFn(st->data);
			f=st->data;
			if(f->Kind==1)
				printf(" %d\n",st->listInNode->num_of_elements);
			else
				printf("\n");
			st=listGetNext(ss->listInNode);
		}
		//listPrint(ss->listInNode);
	}
	return SUCCESS;
}
