/*
 * Map.c
 *
 *  Created on: Dec 6, 2017
 *      Author: ise
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Map.h"
#include "List.h"
#include "Tree.h"

//compare between two map nodes (by their keys).
static int compMapNode (void* m_node1, void* m_node2){ // if it inner- to put static? to put in h?
	if(0==strcmp(((m_node)m_node1)->key, ((m_node)m_node2)->key)){
		return 0;}
	if(strcmp(((m_node)m_node1)->key, ((m_node)m_node2)->key)<0){
		return 2;}
	else{
		return 1;
	}
}


//Copy map node to a new map node.
static void* cpyMapNode (void* m_node1){
	m_node newNode=malloc(sizeof(struct Map_Node)); //create new node- size of Map_Node
	if(newNode==NULL){
		return NULL;}
	newNode->func = ((m_node) m_node1)->func;
	newNode->key= malloc(sizeof(char)*128);// 128 char-To check;
	strcpy(newNode->key,((m_node) m_node1)->key);
	return (void *)newNode;
}


static void freeMapNode (void*  m_node1){
	free(((m_node) m_node1)->key);
	free(((m_node) m_node1));
}

static void printMapNode (void*  m_node1){
	//printf("the address of the function %p",m_node1->func); //do I need to print the address of the function, and how?
	printf("your key is %s",((m_node) m_node1)->key);
}

//create new map
Map createMap(){
	Map m= malloc(sizeof(struct Map_t));//
	if(m==NULL){
		return NULL;}
	m->nodesMap =listCreate(freeMapNode, compMapNode, cpyMapNode , printMapNode); // create the nodesMap
	if(m->nodesMap!=NULL)
		return m;
	destroyMap(m); // if we did not success to create the nodesMap
	m=NULL;
	return NULL;
}

//destroy the Map
void destroyMap(Map m){
	if(m== NULL) return;
	listDestroy(m->nodesMap);
	free(m);
}


m_node createMapNode(char* key, func_t F){
	m_node newNode= malloc(sizeof(struct Map_Node));
	if(newNode==NULL)
		return NULL;
	newNode->func= F;
	newNode->key= malloc(sizeof(char)*128);// 128 char-To check;
	strcpy(newNode->key,key);
	return newNode;
}

//the function get key and function and add to the map
Result InsertPair(Map m, char* key,func_t F){
	m_node N_node= createMapNode(key, F);
	if(N_node==NULL){
		return FAIL;
	}
	listAddNonSorted(m->nodesMap ,N_node);
	return SUCCESS;
}

func_t getFunction(Map m,char* key){
	m_node search_node;
	search_node= (m_node)malloc(sizeof(struct Map_Node));
	if(search_node==NULL){
		return NULL;
	}
	search_node->key=  malloc(sizeof(char)*128);;
	strcpy(search_node->key,key);
	search_node->func=NULL;
	if(m->nodesMap==NULL)
		return NULL;
	m_node found_node;
	found_node= (m_node)listNodeSearchElem(m->nodesMap, search_node);
	free(search_node->key);
	search_node->key=NULL;
	free(search_node);
	search_node=NULL;
	if(found_node==NULL){
		return NULL;
	}
	return found_node->func;
}


m_node searchMapNode(Map m,char* key,func_t F){
		m_node search_node;
		search_node= (m_node)malloc(sizeof(struct Map_Node));
		if(search_node==NULL){
			return NULL;
		}
		search_node->key=  malloc(sizeof(char)*128);;
		strcpy(search_node->key,key);
		search_node->func=F;
		if(m->nodesMap==NULL)
			return NULL;
		m_node found_node;
		found_node= (m_node)listNodeSearchElem(m->nodesMap, search_node);
		free(search_node->key);
		free(search_node);
		return found_node;
}

Result removeMapPair(Map m,char* key,func_t F ){
	m_node search_node;
	search_node= (m_node)malloc(sizeof(struct Map_Node));
	if(search_node==NULL){
		return FAIL;
	}
	search_node= searchMapNode(m, key, F);
	listNodeDelete(m->nodesMap, search_node);// use the freeMapNode and free every relevant thing
	return SUCCESS;
}




