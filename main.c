
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "processcontrol.h"
#include "core.h"


/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
unsigned systemTime = 0; 	// the current system time (up time)
const char* printBoolean(Boolean b) {
	char* truefalse = "FALSE";
	if (b == TRUE) {
		truefalse = "TRUE";
	}
	return truefalse;
}

void printBlockedList(blockedList_t list) {
	blockedList_t process = list;
	printf("-----------\n");
	while (process->next != NULL) {
		printf("process id: %d\n", process->pid);
		process = process->next;
	}
	printf("last process id: %d\n", process->pid);
	printf("------------\n");
}

void testBlockAdd() {
	printf("Adding first process\n");
	addBlocked(1, 5);
	printBlockedList(blockedList);
	printf("Adding more processes\n");
	addBlocked(2, 10);
	addBlocked(3, 10);
	addBlocked(5, 10);
	printBlockedList(blockedList);
}

int main(int argc, char *argv[])
{	// starting point, all processing is done in called functions
	//sim_initSim();		// initialise simulation run-time environment
	//initOS();		// initialise operating system
	//logGeneric("Starting stimulus-based simulation");
	//coreLoop();		// start scheduling loop
	//logGeneric("Simulation complete, shutting down");
	//sim_closeSim();		// shut down simulation envoronment
	//fflush(stdout);			// make sure the output on the console is complete 
	testBlockAdd();
	return 1; 
}