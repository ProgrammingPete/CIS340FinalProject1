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

int main(){


	printf("%d", sizeof(struct node));
	CreateList();

	sleep(2);
	ScanList(End);
	

}

bool isEmpty(){

	return (End == NULL);
}
void PrintList(){
	struct node *temp = End;
	printf("\n[");
	//if (isEmpty() == false){
		/*while(temp->next != Current){
			printf("(%d,%d)", temp->ProcessID,temp->ExecTime);
			temp=temp->next;
		}*/
		do{	
			printf("(%d,%d)", temp->ProcessID,temp->ExecTime);
			temp=temp->next;
		}while(temp != End);
		
		
	//}
	printf("]");
}

void Add(int exectime, int processID){

	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->ProcessID = processID;
	temp->ExecTime= exectime;

	if(isEmpty()){
		End = temp;
		Current = End;
		End->next = End;
		Current = temp;
	}else{
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

	//read file
	while(buff[i] != '\0'){
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
struct node* ScanList(struct node* end){
	//initiate scanning process from the end node
	// decrease exectime by every call of function

	PrintList();
	while(1){
	Current->ExecTime = Current->ExecTime - 1;
	if(Current->ExecTime == 1)
		RemoveCurrent(Current);
	else
		Current=Current->next;
	if(isEmpty()){
		sleep(5);
		exit(1);
	}
		
	PrintList();
	sleep(1);
	
	}
	
	sleep(5);
	return end;
}

struct node* RemoveCurrent(struct node* target){


	//reference to removedLink
	struct node *removedLink = target;
	Current = Current->next;
	

	if(End->next == End){
		End = NULL;
		return removedLink;
	}
	else{
		//find previous node
		struct node* prev = End;
		while(prev->next != target)
			prev = prev->next;
			
		prev->next=target->next;
		//moves the next
		if(target == End)
			End = End->next;

		//this deletes the node
		free(target);
		

		return removedLink;
	}

	return NULL;

}








