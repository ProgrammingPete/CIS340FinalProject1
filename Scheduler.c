/*
 * Scheduler.c
 *
 *  Created on: Apr 14, 2018
 *      Author: ppari
 *
 *	OVerview of the project is that we need to create a circular linked list
 *	that has a popinter called End and Current
 *
 */
#include <stdio.h>
#include <stdbool.h>   // allow boolean operations
#include <stdlib.h>


//global node structure
struct node {
	int ExecTime, ProcessID;
	struct node* next;
};

//Create a linked list from the data of the test1.txt file. Returns the End
//pointer to the end node
struct node * CreateList();

//this adds a node to the end of the list. The end of the list is defined by
// the end pointer. Recieves to interger values, ExecTime and ProcessID
void Add(int, int);

//scans the linked list every one second in order to find the process that needs
//to be removed from the list. Receives the End pointer to obtain the address
// of the node first node and initiate the scanning process. It removes the
//address of the node that should be removed by making it null.
struct node* ScanList(struct node*);

//removes the process that current is pointing to when the process execution time is
//done.Receives current node pointer. USed by ScanList and returns the reference of
// the recently removed node. returns null on empty list
struct node* RemoveCurrent(struct node*);

bool isEmpty();
void PrintList();

struct node* End = NULL;
struct node * Current = NULL;

int main(){

	printf("Hello World");

}

bool isEmpty(){

	return End == NULL;
}
void PrintList(){
	if (isEmpty()){

	}
}

struct node* CreateList(){
	//we need to read the text file
	return End;
}

struct node* RemoveCurrent(struct node* Current){
	if(isEmpty())
		return NULL;
	else{
		//remove node that current is pointing to
	}
}

struct node* ScanList(struct node* End){
	//initiate scanning process from the end node
	return End;
}






