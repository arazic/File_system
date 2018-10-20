/*
 * Map.h
 *
 *  Created on: Nov 26, 2017
 *      Author: ise
 */

#ifndef MAP_H_
#define MAP_H_

#include <string.h>
#include <stdbool.h>
#include "List.h"
#include "Tree.h"


typedef struct Map_t* Map;
typedef struct Map_Node* m_node;
typedef Result (*func_t)(Tree t, char*);

struct Map_Node{
	char* key;
	Result (*func) (Tree t, char *);
};

struct Map_t{
	List nodesMap;
};

Map createMap();
void destroyMap(Map m);
Result InsertPair(Map m, char* key,func_t F);
func_t getFunction(Map m,char* key);
Result removeMapPair(Map m,char* key,func_t F );


#endif /* MAP_H_ */
