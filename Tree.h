/*
 * Tree.h
 *
 *  Created on: Dec 20, 2017
 *      Author: ise
 */

#ifndef TREE_H_
#define TREE_H_

#include "List.h"

typedef struct nodeTree_t* structTreeElement;
typedef struct Tree_t* Tree;

//create new Tree
Tree treeCreate(freeFunction freeFunc, compareFunction cmpFunc, copyFunction cpyFunc, printFunction printFunc);

//add data in random position
Result Add(Tree tree,Element elem);

//add in specipic position
Result AddIn(Tree tree, Element elem,List position);

//remove node
Result Remove(Tree tree,List position);

Result existRoute(Tree t, List position);

structTreeElement treeSearch(Tree t, List position);

Element getTreeData(Tree t, List position);

//new contant in node
Result Reassign(Tree tree,List position,Element contant);

//To print just part of the tree
Result lsPrint(Tree tree,List position,int recursive);

Result existRoute(Tree t,List position);
Element treeGetData(Tree t,List position);
void Print(Tree tree);
#endif /* TREE_H_ */
