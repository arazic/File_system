/*
 * main.c
 *
 *  Created on: Dec 11, 2017
 *      Author: ise
 */

#include "Map.h"
#include "Tree.h"
#include "FolFil.h"
#include "List.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ThePathSIZE 2000
#define TheFuncSIZE 10
#define TheInputSIZE 2000
#define WordsInCommand 200
#define MaxNameSize 2000

typedef void* Element;

Result CheckFunc (char* e){
	printf("your node value is %s\n", e);
	return SUCCESS;
}


int getWord(char* TheLine, char** SpliteCommand){
	int j=0;
	int ctr=0;
	int i;
	for(i=0;i<=(strlen(TheLine));i++)
	{
		if(TheLine[i]==' '||TheLine[i]=='\0')
		{
			SpliteCommand[ctr][j]='\0';
			ctr++;  //for next word
			j=0;    //for next word, init index to 0
		}
		else
		{
			SpliteCommand[ctr][j]=TheLine[i];
			j++;
		}
	}
	return ctr;
}

void SpliteTheFunc(char* TheLine, char* TheFunc, char* TheRest){
	int j=0;
	int i;
	for(i=0;i<=(strlen(TheLine));i++)
	{
		while((TheLine[i]!=' ')&&(TheLine[i]!='\0')){
			TheFunc[j]=TheLine[i];
			j++;
			i++;
		}
		j=0;
		i++;
		while(TheLine[i]!='\0'){
			TheRest[j]=TheLine[i];
			j++;
			i++;
		}
	}
}

int PathSplited(char* ThePath, char** PathSplitedArray){
	int k;
	int j=0;
	int ctr=1;
	int i;

	for (k=0; k<WordsInCommand; k++)
		memset(PathSplitedArray[k], 0, ThePathSIZE);

	for(i=0;i<=(strlen(ThePath)-1);i++)
	{
		if(ThePath[i+1]=='/')
		{
			PathSplitedArray[ctr-1][j]='\0';
			ctr++;  //for next word
			j=0;    //for next word, init index to 0
		}
		else
		{
			PathSplitedArray[ctr-1][j]=ThePath[i+1];
			j++;
		}
	}
	return ctr;
}
int compFFnode(void* FolFil1, void* FolFil2){
	if(0==strcmp(((FolFil)FolFil1)->name, ((FolFil)FolFil2)->name)){
		return 0;}
	if(strcmp(((FolFil)FolFil1)->name, ((FolFil)FolFil2)->name)<0){
		return 2;}
	else{
		return 1;
	}
}

void* cpyFFnode (void* FolFil1){
	FolFil newFF=malloc(sizeof(struct t_FolFil)); //create new node- size of Map_Node
	FolFil old=FolFil1;
	if(newFF==NULL){
		return NULL;}
	newFF->Kind = ((FolFil) FolFil1)->Kind;
	int k=strlen(old->name);
	newFF->name= malloc(sizeof(char)*(k+1));// 128 char-To check;
	strcpy(newFF->name,((FolFil) FolFil1)->name);
	return (void *)newFF;
}

void freeFFnode (void*  FolFil1){
	free(((FolFil) FolFil1)->name);
	free(((FolFil) FolFil1));
	return;

}

void printFFnode (void* FolFil1){
	printf("%s",((FolFil) FolFil1)->name);
	return;
}

FolFil allocateFolFil(){
	FolFil newFF= (FolFil)malloc(sizeof(struct t_FolFil));
	if(newFF==NULL)
		return  NULL;
	newFF->name= (char*)malloc(MaxNameSize*sizeof(char));
	if(newFF->name==NULL)
		return NULL;
	return newFF;
}

void freeFolFil(FolFil FF){
	free(FF->name);
	FF->name=NULL;
	free(FF);
	FF=NULL;
}

FolFil createFolFil(int Kind1, char* name1, int nameSize1){
	char* Thename=name1;
	int nameSize=nameSize1;
	FolFil newFF= (FolFil)malloc(sizeof(struct t_FolFil));
	if(newFF==NULL){
		return (FolFil)NULL;
	}
	else{
		newFF->Kind=Kind1;
		newFF->name= (char*)malloc(nameSize*sizeof(char));
		strcpy(newFF->name, Thename);
	}
	return newFF;
}

void destroyFolFil(FolFil FF){
	free(FF->name);
	FF->name=NULL;
	free(FF);
	FF=NULL;
}

//create routh with the last position- lastPos is a file
List makePositionListWithLast (int NumWords, char**PathSplitedArray, freeFunction freeFFnode1, compareFunction compFFnode1, copyFunction cpyFFnode1 , printFunction printFFnode1){
	FolFil FF;
	List FF_Position;
	int j;
	FF_Position= listCreate(freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1);

	for(j=NumWords-1; j>=0; j--){
		FF= (FolFil)malloc(sizeof(struct t_FolFil));
		if(FF==NULL){
			return NULL;}
		else{
			FF->Kind=0;
			FF->name= (char*)malloc(sizeof((PathSplitedArray[NumWords-1]))*sizeof(char));
			strcpy(FF->name, (char*)PathSplitedArray[j]);
			listAddNonSorted(FF_Position, FF);
		}
	}
	return FF_Position;
}

//create routh with the last position- lastPos is a folder
List makePositionListWithLastFol (int NumWords, char**PathSplitedArray, freeFunction freeFFnode1, compareFunction compFFnode1, copyFunction cpyFFnode1 , printFunction printFFnode1){
	FolFil FF;
	List FF_Position;
	int j;
	FF_Position= listCreate(freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1);

	for(j=NumWords-1; j>=0; j--){
		FF= (FolFil)malloc(sizeof(struct t_FolFil));
		if(FF==NULL){
			return NULL;}
		else{
			FF->Kind=1;
			FF->name= (char*)malloc(sizeof((PathSplitedArray[NumWords-1]))*sizeof(char));
			strcpy(FF->name, (char*)PathSplitedArray[j]);
			listAddNonSorted(FF_Position, FF);
		}
	}
	return FF_Position;
}
//create routh with no last position
List makePositionList(int NumWords, char**PathSplitedArray, freeFunction freeFFnode1, compareFunction compFFnode1, copyFunction cpyFFnode1 , printFunction printFFnode1){
	FolFil FF;
	List FF_Position;
	int j;
	FF_Position= listCreate(freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1);

	for(j=NumWords-2; j>=0; j--){
		FF= (FolFil)malloc(sizeof(struct t_FolFil));
		if(FF==NULL){
			return NULL;}
		else{
			FF->Kind=1;
			FF->name= (char*)malloc(sizeof((PathSplitedArray[NumWords-1]))*sizeof(char));
			strcpy(FF->name, (char*)PathSplitedArray[j]);
			listAddNonSorted(FF_Position, FF);
		}
	}
	return FF_Position;
}

List makePositionListOren(int NumWords, char**PathSplitedArray, freeFunction freeFFnode1, compareFunction compFFnode1, copyFunction
		cpyFFnode1 , printFunction printFFnode1){
	FolFil FF;
	List FF_Position;
	int j;
	FF_Position= listCreate(freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1);

	for(j=NumWords-1; j>=0; j--){
		FF= (FolFil)malloc(sizeof(struct t_FolFil));
		if(FF==NULL){
			return NULL;}
		else{
			FF->Kind=1;
			FF->name= (char*)malloc(sizeof((PathSplitedArray[NumWords-1]))*sizeof(char));
			strcpy(FF->name, (char*)PathSplitedArray[j]);
			listAddNonSorted(FF_Position, FF);
		}
	}
	return FF_Position;
}


char ** allocPathSplitedArray (char* ThePath){
	char** PathSplitedArray;
	int i;

	PathSplitedArray = (char **)malloc(sizeof(char*)*WordsInCommand);
	if(PathSplitedArray==NULL){
		return NULL;
	}
	for (i=0; i<WordsInCommand; i++){
		PathSplitedArray[i] = (char *)malloc(sizeof(char)*ThePathSIZE);
		if(PathSplitedArray[i]==NULL)
			return NULL;
	}
	return PathSplitedArray;
}

void destroyPathSplitedArray(char** PathSplitedArray){
	int i;

	if(PathSplitedArray!=NULL){
		for (i=0; i<WordsInCommand; i++){
			free(PathSplitedArray[i]);
			PathSplitedArray[i]=NULL;
		}
		free(PathSplitedArray);
		PathSplitedArray=NULL;
	}
	return;
}

/*
char* exactNotExist(Tree t, char**PathSplitedArray, int listSize, freeFunction freeFFnode1, compareFunction compFFnode1, copyFunction cpyFFnode1 , printFunction printFFnode1){
	char** l= allocPathSplitedArray(PathSplitedArray);
	List check;
	FolFil FF;
	int j;
	int exist=1;

	check= listCreate(freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1);

	for(j=0; j<listSize&&(exist==1); j++){
		check=makePositionList(listSize-j, PathSplitedArray, freeFFnode1, compFFnode1, cpyFFnode1 , printFFnode1){
		if(existRoute(t, check)==SUCCESS){
			FFnot allocateFolFil();
				if(FFtoCopy==NULL)
					ans= FAIL;;
				FFtoCopy= (FolFil)getTreeData(t, FF_From);
		}
	}

}
 */

Result mkdir(Tree t, char* ThePath){
	char** PathSplitedArray;
	int NumWordsPath;
	List FF_Position;
	FolFil FFtoAdd;

	Result ans;

	PathSplitedArray=allocPathSplitedArray(ThePath);
	if(PathSplitedArray==NULL){
		ans= FAIL;}

	NumWordsPath= PathSplited(ThePath, PathSplitedArray);
	if(NumWordsPath==0||ThePath[0]!='/'){
		printf("Path %s does not exist\n",ThePath);
		ans= FAIL;}
	else{
		if(NumWordsPath==1){
			FFtoAdd= createFolFil(1 , PathSplitedArray[NumWordsPath-1], sizeof((PathSplitedArray[NumWordsPath-1])) );
			ans=Add(t, FFtoAdd);
			if(FFtoAdd!=NULL){
				destroyFolFil(FFtoAdd);
			}
		}
		else{
			FFtoAdd= createFolFil(1 , PathSplitedArray[NumWordsPath-1], sizeof((PathSplitedArray[NumWordsPath-1])) );

			FF_Position= makePositionList(NumWordsPath, PathSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);

			if(existRoute(t, FF_Position)==FAIL){
				printf("Path %s does not exist\n",PathSplitedArray[0]);
			}
			else{
				ans=AddIn(t, FFtoAdd, FF_Position);
			}
			listDestroy(FF_Position);
			if(FFtoAdd!=NULL){
				destroyFolFil(FFtoAdd);
			}
		}
	}

	destroyPathSplitedArray(PathSplitedArray);

	return ans;
}

Result touch(Tree t, char* ThePath){
	char** PathSplitedArray;
	int NumWordsPath;
	List FF_Position;
	FolFil FFtoAdd;
	Result ans;

	PathSplitedArray=allocPathSplitedArray(ThePath);
	if(PathSplitedArray==NULL){
		ans= FAIL;}

	NumWordsPath= PathSplited(ThePath, PathSplitedArray);
	if(NumWordsPath==0||ThePath[0]!='/'){
		printf("Path %s does not exist\n",ThePath);
		ans= FAIL;}
	else{
		if(NumWordsPath==1){
			FFtoAdd= createFolFil(0 , PathSplitedArray[NumWordsPath-1], sizeof((PathSplitedArray[NumWordsPath-1])) );
			ans=Add(t, FFtoAdd);
			if(FFtoAdd!=NULL){
				destroyFolFil(FFtoAdd);
			}
		}
		else{
			FFtoAdd= createFolFil(0 , PathSplitedArray[NumWordsPath-1], sizeof((PathSplitedArray[NumWordsPath-1])) );
			FF_Position= makePositionList(NumWordsPath, PathSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);

			if(existRoute(t, FF_Position)==FAIL){
				printf("Path %s does not exist\n",PathSplitedArray[0]);
			}
			else{
				ans=AddIn(t, FFtoAdd, FF_Position);}
			listDestroy(FF_Position);

			if(FFtoAdd!=NULL){
				destroyFolFil(FFtoAdd);
			}
		}
	}

	destroyPathSplitedArray(PathSplitedArray);

	return ans;
}


Result mv(Tree t, char* ThePath){

	char** routeSplited;
	char* from;
	char* too;
	char** fromSplitedArray;
	char** toSplitedArray;
	int numRouteFrom, numRouteTo, numOfroute;
	List FF_From, FF_To, FF_ToNoLast;
	FolFil FFtoMove, LastFolFil, TheSwitchFolFil;
	Result ans;

	routeSplited=allocPathSplitedArray(ThePath);

	from=malloc(sizeof(char)*ThePathSIZE);
	if(from==NULL)
		return FAIL;
	too=malloc(sizeof(char)*ThePathSIZE);
	if(too==NULL)
		return FAIL;

	memset(from, 0, ThePathSIZE);
	memset(too, 0, ThePathSIZE);

	numOfroute= getWord(ThePath, routeSplited);
	from= routeSplited[0];
	too= routeSplited[1];

	if(from[0]!='/'){
		printf("Path %s does not exist\n",from);
		return FAIL;
	}
	if((too[0])!='/'){
		printf("Path %s does not exist\n",too);
		return FAIL;
	}
	else{
		fromSplitedArray=allocPathSplitedArray(from);
		toSplitedArray=allocPathSplitedArray(too);
		if(fromSplitedArray==NULL){
			ans= FAIL;}
		if(toSplitedArray==NULL){
			ans= FAIL;}

		numRouteFrom= PathSplited(from, fromSplitedArray);
		numRouteTo= PathSplited(too, toSplitedArray);

		FFtoMove= allocateFolFil();
		LastFolFil= allocateFolFil();
		if(FFtoMove==NULL||LastFolFil==NULL)
			return FAIL;

		FF_From= makePositionListWithLast(numRouteFrom, fromSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);
		//The position List that we take from (with no the moved file)

		FFtoMove= (FolFil)getTreeData(t, FF_From);

		FF_To= makePositionListWithLast(numRouteTo, toSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);

		LastFolFil= (FolFil)getTreeData(t, FF_To); //this is the last FolFil in <to> route.
		// we will check if it a new file name or a folder to move to.
		FF_ToNoLast=makePositionList(numRouteTo, toSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);

		TheSwitchFolFil= allocateFolFil();
		if(existRoute(t, FF_ToNoLast)==FAIL){
					printf("Path %s does not exist\n",toSplitedArray[0]);
					return FAIL;
				}
		else{
		if(FFtoMove==NULL){
			if(FFtoMove==NULL){
				printf("Path %s does not exist\n",fromSplitedArray[0]);
				ans= FAIL;}
		}
		else{
			if(LastFolFil!=NULL){
			if(((FolFil)LastFolFil)->Kind==1){
				if(Remove(t, FF_From)==FAIL) //remove the file from the beginning place.
					ans= FAIL;
				if(AddIn(t,FFtoMove, FF_To)==FAIL) //Add to the new position.
					ans= FAIL;
			}
			}
			else{
				Remove(t, FF_From);
				strcpy(TheSwitchFolFil->name, toSplitedArray[numRouteTo-1]);
				TheSwitchFolFil->Kind= FFtoMove->Kind;
				if(AddIn(t, TheSwitchFolFil, FF_ToNoLast)==FAIL){
				ans= FAIL;
					}
				else{
					ans= SUCCESS;
				}
				destroyFolFil(TheSwitchFolFil);
			}
		}
		}
	}
	destroyPathSplitedArray(fromSplitedArray);
	destroyPathSplitedArray(toSplitedArray);
	return ans;
}


Result cp(Tree t, char* ThePath){
	char** routeSplited;
	char* from;
	char* too;
	char* NotExist;
	char** fromSplitedArray;
	char** toSplitedArray;
	int numRouteFrom, numRouteTo, numOfroute;
	List FF_From, FF_To, FF_ToNoLast;
	FolFil originalFF, getFF;
	Result ans;

	routeSplited=allocPathSplitedArray(ThePath);

	from=malloc(sizeof(char)*ThePathSIZE);
	if(from==NULL)
		return FAIL;
	too=malloc(sizeof(char)*ThePathSIZE);
	if(too==NULL)
		return FAIL;

	memset(from, 0, ThePathSIZE);
	memset(too, 0, ThePathSIZE);

	numOfroute= getWord(ThePath, routeSplited);
	from= routeSplited[0];
	too= routeSplited[1];

	if(from[0]!='/'){
		printf("Path %s does not exist\n",from);
		return FAIL;
	}
	if((too[0])!='/'){
		printf("Path %s does not exist\n",too);
		return FAIL;
	}
	else{
		fromSplitedArray=allocPathSplitedArray(from);
		toSplitedArray=allocPathSplitedArray(too);
		if(fromSplitedArray==NULL){
			ans= FAIL;}
		if(toSplitedArray==NULL){
			ans= FAIL;}

		numRouteFrom= PathSplited(from, fromSplitedArray);
		numRouteTo= PathSplited(too, toSplitedArray);

		originalFF= allocateFolFil();
		if(originalFF==NULL)
			ans= FAIL;;

		getFF= allocateFolFil();
		if(originalFF==NULL)
			ans= FAIL;;

		FF_From= makePositionListWithLast(numRouteFrom, fromSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);
		//The position List that we take from (with no the moved file)

		if(existRoute(t, FF_From)==FAIL){
			printf("Path %s does not exist\n",fromSplitedArray[0]);
			return FAIL;
		}

		originalFF= (FolFil)getTreeData(t, FF_From);

		FF_To= makePositionListWithLast(numRouteTo, toSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);
		// we will check if it a new file name or a folder to move to.

		FF_ToNoLast=makePositionList(numRouteTo, toSplitedArray, freeFFnode, compFFnode, cpyFFnode , printFFnode);
		if(originalFF==NULL){
			printf("File %s does not exist\n",fromSplitedArray[0]);
			ans= FAIL;
		}
		else{
			if(((FolFil)originalFF)->Kind==1){
				printf("File %s does not exist\n",fromSplitedArray[0]);
				ans= FAIL;
			}
			else{
				if(existRoute(t, FF_ToNoLast)==FAIL){
					printf("Path %s does not exist\n",toSplitedArray[0]);
					ans= FAIL;;
				}
				else{

					strcpy(getFF->name, toSplitedArray[numRouteTo-1]);
					getFF->Kind= originalFF->Kind;
					if(AddIn(t, getFF, FF_ToNoLast)==FAIL){
						ans= FAIL;
					}
					else{
						ans= SUCCESS;
					}
				}
			}
		}
		//listPrint(FF_From);
		//	listPrint(FF_To);

		destroyPathSplitedArray(fromSplitedArray);
		destroyPathSplitedArray(toSplitedArray);
		return ans;
	}
}

Result ls(Tree t, char* ThePath){
	char** commandSplited;
	char* route;
	char* flag;
	char** routeSplited;
	int numRoute, numOfroute;
	List FF_Position, FF_PositionWithNoLast;
	Result ans;
	FolFil LastOne;

	commandSplited=allocPathSplitedArray(ThePath);

	route=malloc(sizeof(char)*ThePathSIZE);
	if(route==NULL)
		return FAIL;

	if(0==strcmp(ThePath,""))
	{
		numOfroute=0;
	}
	else{
		numOfroute= getWord(ThePath, commandSplited);
		if(numOfroute==2||numOfroute==1){
			if(numOfroute==2){
				flag= commandSplited[0];
				route= commandSplited[1];
			}
			if(numOfroute==1){
				flag= NULL;
				route= commandSplited[0];
			}

			if(route[0]!='/'){
				printf("Path %s does not exist\n",route);
				ans= FAIL;
			}
			else{
				routeSplited=allocPathSplitedArray(route);
				if(routeSplited==NULL){
					ans= FAIL;}
				numRoute= PathSplited(route, routeSplited);
				FF_PositionWithNoLast=makePositionListOren(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
				LastOne=getTreeData(t, FF_PositionWithNoLast);
				if(LastOne!=NULL){
					if(LastOne->Kind==0){
						FF_Position= makePositionListWithLast(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
					}//The position List that we want to print from, that the last is file
					else{
						FF_Position= makePositionListWithLastFol(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
						//The position List that we want to print from, that the last is folder
					}
				}
				if(existRoute(t, FF_Position)==FAIL){
					printf("File %s does not exist\n",route);
					ans= FAIL;
				}
				else{
					if(flag!=NULL&& route!=NULL)
						ans= lsPrint(t, FF_Position , 1);
					if(flag==NULL&& route!=NULL)
						ans= lsPrint(t, FF_Position , 0);
				}
			}
			listDestroy(FF_Position);
			destroyPathSplitedArray(routeSplited);
		}
	}
	if(numOfroute==0){
		flag= NULL;
		route= NULL;
		ans= lsPrint(t, NULL, 0);
	}
	destroyPathSplitedArray(commandSplited);

	return ans;
}


Result rm(Tree t, char* ThePath){
	char** commandSplited;
	char* route;
	char* flag;
	char** routeSplited;
	int numRoute, numOfroute, i;
	List FF_Position, FF_PositionWithNoLast;
	Result ans;
	FolFil LastOne;

	commandSplited=allocPathSplitedArray(ThePath);

	route=malloc(sizeof(char)*ThePathSIZE);
	if(route==NULL)
		return FAIL;

	for(i=0; i<WordsInCommand; i++)
		memset(commandSplited[i], 0, ThePathSIZE);


	numOfroute= getWord(ThePath, commandSplited);
	if(numOfroute==2||numOfroute==1){
		if(numOfroute==2){
			flag= commandSplited[0];
			route= commandSplited[1];
		}
		if(numOfroute==1){
			flag= NULL;
			route= commandSplited[0];
		}

		if(route[0]!='/'){
			printf("Path %s does not exist\n",route);
			ans= FAIL;
		}
		else{
			routeSplited=allocPathSplitedArray(route);
			if(routeSplited==NULL){
				ans= FAIL;}
			numRoute= PathSplited(route, routeSplited);
			FF_PositionWithNoLast=makePositionList(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
			FF_Position= makePositionListWithLastFol(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
			LastOne=getTreeData(t, FF_Position);
			if(LastOne!=NULL){
				if(LastOne->Kind==0){
					//FF_Position= makePositionListWithLast(numRoute, routeSplited, freeFFnode, compFFnode, cpyFFnode , printFFnode);
					Remove(t, FF_Position);
				}//The position List that we want to print from, that the last is file
				else{
					if(flag==NULL){
						printf("The Path /%s describes a folder\n",LastOne->name);
					}
					else{
						Remove(t, FF_Position);
					}
					//The position List that we want to print from, that the last is folder
				}
			}
		}
		listDestroy(FF_Position);
		destroyPathSplitedArray(routeSplited);
		destroyPathSplitedArray(commandSplited);
	}
	if(numOfroute==0){
		flag= NULL;
		route= NULL;
		ans= lsPrint(t, NULL, 0);
	}

	//listPrint(FF_Position);

	return ans;
}

Result Exit(Tree t, char* ThePath){
	return FAIL;
}


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	Tree t;
	char* TheInput= malloc(sizeof(char)*TheInputSIZE);
	char* TheFunction= malloc(sizeof(char)*TheFuncSIZE);
	char* ThePath= malloc(sizeof(char)*ThePathSIZE);
	char* TheRest = malloc(sizeof(char)*TheInputSIZE);
	char** SpliteCommand;
	int i, numOfWords=0;
	numOfWords++;
	Map m= createMap();
	Result rMkdir, rExit, rTouch, rMv, rCp, rLs, rRm ;
	Result end=SUCCESS;
	func_t currentFunc;
	Result foundFunction;
	//enter the functions to map

	rMkdir= InsertPair(m, "mkdir" , mkdir);
	rExit=InsertPair(m, "exit", Exit);
	rTouch=InsertPair(m, "touch", touch);
	rMv=InsertPair(m, "mv", mv);
	rCp=InsertPair(m, "cp", cp);
	rLs= InsertPair(m, "ls", ls);
	rRm= InsertPair(m, "rm", rm);

	t=treeCreate(freeFFnode, compFFnode, cpyFFnode , printFFnode);

	SpliteCommand = (char **)malloc(sizeof(char*)*WordsInCommand);
	for (i=0; i<WordsInCommand; i++)
		SpliteCommand[i] = (char *)malloc(sizeof(char)*ThePathSIZE);

	printf("Hello you!\n");
	while(end==SUCCESS){

		printf("@>");
		scanf("%[^\n]%*c", TheInput);
		SpliteTheFunc(TheInput, TheFunction, TheRest);

		if(!TheInput[0]=='\0'){
			if(getFunction(m,TheFunction)!=NULL){
				if(0==strcmp(TheFunction,"mkdir")|| 0==strcmp(TheFunction,"touch") ||0==strcmp(TheFunction,"exit")){
					//numOfWords= getWord(TheInput, SpliteCommand);
					ThePath= TheRest;
					currentFunc=getFunction(m,TheFunction);
					foundFunction= currentFunc(t, ThePath);
					if(0==strcmp(TheFunction,"exit")){
						end=FAIL;
					}
				}
				else{
					currentFunc=getFunction(m,TheFunction);
					foundFunction= currentFunc(t, TheRest);
				}
			}
			else{
				printf("Unknown command %s\n", TheFunction);
			}
			if(0!=strcmp(TheFunction,"exit")){
				for (i=0; i<WordsInCommand; i++)
					memset(SpliteCommand[i], 0, ThePathSIZE);

				memset(TheInput, 0, TheInputSIZE);// empty the used input
				memset(TheFunction, 0, TheFuncSIZE); // empty the used function
				memset(ThePath, 0, ThePathSIZE);//empty the used path
				memset(TheRest, 0, TheInputSIZE); // empty the used rest
			}
		}// While- the prog is not end
	}
	if(SpliteCommand!=NULL){
		for (i=0; i<WordsInCommand; i++){
			free(SpliteCommand[i]);
			SpliteCommand[i]=NULL;
		}
		free(SpliteCommand);
		SpliteCommand=NULL;
	}
	free(TheInput);
	free(TheFunction);
	if(ThePath[0]!='\0')
		free(ThePath);
	if(TheRest[0]!='\0')
		free(TheRest);

	destroyMap(m);
	return 0;
}

