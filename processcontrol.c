/* Functions for control and administration of processes including  */
/* creation, destruction, blocked-control...						*/
/* for comments on the functions see the associated .h-file 		*/

/* ----------------------------------------------------------------	*/
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "processcontrol.h"
#include "simruntime.h"

/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
PCB_t processTable[NUM_PROCESSES+1]; 	// the process table
readyList_t readyList;	// list of runnable processes
blockedList_t blockedList;	// pointer to blocked process

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/
blockedListElement_t blockedOne; // the only process that can be blocked 
/*this must be extended to a suitable data structure for multiprogramming */

readyListElement_t readyOne;	// the only process ready in the batch system 
/*this must be extended to a suitable data structure for multiprogramming */



/* ---------------------------------------------------------------- */
/* Functions for administration of processes in general 			*/
/* ---------------------------------------------------------------- */

pid_t getNextPid()
/* Typically the PID is the index into the process table, thus the pool  	*/
/* for PIDs is limited by the size of the process table. If the end of the	*/
/* process table is reached, new PIDs are assigned by re-using unused 		*/
/* entries in the process table. 											*/
/* If no new PID can be returned (i.e. the process table is full, zero is 	*/
/* returned, which is not a valid PID. 										*/

{
	static unsigned pidCounter = 0;
	// determine next available pid. 
	for (int i = 0; i < NUM_PROCESSES; i++) {
		pidCounter++; 
		if (pidCounter > NUM_PROCESSES) pidCounter = 1; 
		if (!processTable[pidCounter].valid) return pidCounter;
	}
	/* If the loop is completed there was no free entry in the process table */
	return 0;	/* not a valid PID indicating an error  */
}

Boolean deleteProcess(pid_t pid)
/* Voids the PCB of the process with the given pid, this includes setting 	*/
/* the valid-flag to invalid and setting other values to invalid values.	*/
/* retuns FALSE on error and TRUE on success								*/
{
	if (pid == NO_PROCESS)
		return FALSE;
	else {	/* PCB correctly passed, now delete it */
		processTable[pid].valid = FALSE;
		processTable[pid].pid = 0;
		processTable[pid].ppid = 0;
		processTable[pid].ownerID = 0;
		processTable[pid].start = 0;
		processTable[pid].duration = 0;
		processTable[pid].usedCPU = 0;
		processTable[pid].type = os;
		processTable[pid].status = ended;
		return TRUE;
	}
}

/* ---------------------------------------------------------------- */
/* Functions for administration of blocked processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/


Boolean initBlockedList(void)
/* Initialise the blocked process control data structure					*/
/* (no blocked processes exist at initialisation time of the os)			*/
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
{
	blockedList = NULL;
	return TRUE;
}

Boolean addBlocked(pid_t pid, unsigned blockDuration)
// if list not empty, find the tail and add next to it
{
	processTable[pid].status = blocked;			// change process state to "blocked"
	blockedList_t newBlock = malloc(sizeof(blockedList_t));
	
	if (newBlock != NULL) {
		newBlock->pid = pid;
		newBlock->IOready = systemTime + blockDuration;
		newBlock->next = NULL;
	}
	if (blockedList == NULL || blockedList->IOready >= newBlock->IOready) {
		blockedList = newBlock;
	}
	else {
		//create a block which holds this process
		
		//find the last added process (tail)
		blockedList_t tail = blockedList;
		while (tail->next != NULL && tail->next->IOready < newBlock->IOready) {
			tail = tail->next;
		}

		// link tail and newBlock
		tail->next = newBlock;
		newBlock->prev = tail;
	}
	return TRUE;
}

Boolean removeBlocked(pid_t pid)
// remove a process from blocked list
{
	int count = 0;
	blockedList_t toDelete = blockedList;
	while (toDelete->next != NULL) {		// find the process to delete
		if (toDelete->pid == pid) {
			break;
		}
		toDelete = toDelete->next;
		count++;							// count index
	}

	//if its tail
	if (toDelete->next == NULL && count > 1) {
		printList(blockedList);
		toDelete->prev->next = NULL;		//make previous element the tail
	}
	// if its head
	else if (count == 0) {
		blockedList = toDelete->next;       // make list start from the next process
	}
	//between head and tail processses
	else {
		toDelete->prev->next = toDelete->next;		// link previous and next processes
		toDelete->next->prev = toDelete->prev;
		toDelete = NULL;							//delete
	}
	return TRUE;
}

Boolean isBlockedListEmpty(void)
/* predicate returning TRUE if any blocked process exists, FALSE if no		*/
/* blocked processes exist													*/
{
	return (blockedList == NULL);
}

blockedListElement_t *headOfBlockedList()
/* returns a pointer to the first element of the blocked list				*/
/* MUST be implemented for simulation purposes								*/			
{
	if (!isBlockedListEmpty()) {
		return blockedList;	// return pointer to the only blocked element remembered
	} 
	else return NULL;		// empty blocked list has no first element
}


/* ---------------------------------------------------------------- */
/* Functions for administration of ready processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- The ready list is sorted by not decreasing start-times			*/
/*			(i.e. first process to become ready is always head of the list	*/
/*      															*/

Boolean initReadyList(void)
/* Initialise the ready process control data structure						*/
/* (no ready processes exist at initialisation time of the os)				*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the ready process in        xxxx */
/* xxxx batch processing. A ready list needs to be implemented 		   xxxx */
{
	readyList = NULL;
	return TRUE;
}

Boolean addReady(pid_t pid)	
// add a process to the ready list
{
	processTable[pid].status = ready;			// change process state to "ready"
	readyList_t newBlock = malloc(sizeof(readyList_t));
	if (newBlock != NULL) {
		newBlock->pid = pid;
		newBlock->next = NULL;
	}
	if (readyList != NULL) {
												//find the last added process (tail)
		readyList_t tail = readyList;
		while (tail->next != NULL) {
			tail = tail->next;
		}

		// link tail and newBlock
		tail->next = newBlock;
		newBlock->prev = tail;
	}
	else {
		// when list is empty
		readyList = newBlock;
	}
	return TRUE;
}

Boolean removeReady(pid_t pid)
{
	int count = 0;
	readyList_t toDelete = readyList;
	while (toDelete->next != NULL) {		//find the process to delete
		if (toDelete->pid == pid) {
			break;
		}
		toDelete = toDelete->next;
		count++;							//count the index of the process
	}

	//if its tail
	if (toDelete->next == NULL && count > 1) {
		toDelete->prev->next = NULL;
	}
	// if its head
	else if (count == 0) {
		readyList = toDelete->next;
	}
	//between head and tail
	else {
		toDelete->prev->next = toDelete->next;		// link previous process to next process
		toDelete->next->prev = toDelete->prev;
		toDelete = NULL;							// delete
	}
	return TRUE;
}

Boolean isReadyListEmpty(void)
/* predicate returning TRUE if any ready process exists, FALSE if no		*/
/* ready processes exist													*/
{
	return (readyList == NULL);
}

readyListElement_t* headOfReadyList()
/* returns a pointer to the first element of the ready list				*/
/* MUST be implemented for simulation purposes								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
{
	if (!isReadyListEmpty()) {
		return readyList;	// return pointer to the first element
	}
	else return NULL;		// empty ready list has no first element
}

