/*
 * Scheduler.c
 *
 *  Created on: Apr 14, 2018
 *      Author: ppari
 *
 *	OVerview of the project is that we need to create a circular linked list
 *	that has a pointer called End and Current
 *
 */
#include <stdio.h>
#include <stdbool.h>   // allow boolean operations
#include <stdlib.h>
#include <fcntl.h>  //files


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

//explains itself
bool isEmpty();
void PrintList();

struct node * End = NULL;
struct node * Current = NULL;
struct node * prev = NULL;

int main(){

	printf("Hello World");
	CreateList();

	while(!isEmpty()){
		PrintList();
		ScanList();
		sleep(1);
	}

}

bool isEmpty(){

	return End == NULL;
}
void PrintList(){
	struct node *temp = End;
	printf("\n[");
	if (!isEmpty()){
		while(temp->next != End){
			printf("(%d,%d)", temp->ProcessID,temp->ExecTime);
			temp=temp->next;
		}
	}
	printf("]");
}

void Add(int exectime, int processID){
	if(isEmpty()){
		End = (struct node*)malloc(sizeof(struct node));
		Current = (struct node*)malloc(sizeof(struct node));
		End->ExecTime = exectime;
		End->ProcessID = processID;
		End->next = End;
		Current = End;
	}else{

		struct node *temp = (struct node*)malloc(sizeof(struct node));
		temp->ExecTime = exectime;
		temp->ProcessID = processID;
		temp->next = End->next;
		End->next = temp;
		End = temp;
	}
}

struct node* CreateList(){
	FILE * file;
	//buffer
	char buff[100];
	int i = 0, exec, proc;
	file = fopen("test1.txt", "r");

	//read into buffer
	fread(buff,1, 100,file);
	fclose(file);

	//allocate memory

	//read file
	while(buff[i] != 0){
		if(buff[i] == 'P'){
			//converts to int
			proc = buff[i+4] - '0';
			exec = buff[i+6] - '0';
			Add(exec,proc);
		}
		i++;
	}

	return End;

}
struct node* ScanList(){
	//initiate scanning process from the end node
	// decrease exectime by every call of function
	prev = Current;
	Current = Current->next;
	Current->ExecTime = Current->ExecTime - 1;

	if(Current->ExecTime == 1)
		RemoveCurrent(Current);

	return Current;
}

struct node* RemoveCurrent(struct node* current){


	//reference to removedLink
	struct node *removedLink = current;
	if(isEmpty())
		return NULL;
	else if(current->next == current){
		//this is the last node in the linked list
		current = NULL;
		return removedLink;
	}else{
		prev->next = current->next;
		current = NULL;
		current->next = NULL;
		free(current);

		return removedLink;
	}
	return removedLink;

}








