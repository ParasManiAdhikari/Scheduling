
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "processcontrol.h"
#include "core.h"


/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
unsigned systemTime = 0; 	// the current system time (up time)

void testBlockAddRemove() {
	addBlocked(1, 5);
	addBlocked(2, 10);
	addBlocked(3, 10);
	addBlocked(5, 10);
	addBlocked(7, 10);
	printf("Block List: \n");
	printList(blockedList);
	removeBlocked(7);
	printList(blockedList);
}

void testReadyAddRemove() {
	printf("ReadyList: ");
	addReady(2);
	addReady(13);
	addReady(5);
	addReady(7);
	printList(readyList);
	removeReady(13);
	printList(readyList);
}


int main(int argc, char *argv[])
{	// starting point, all processing is done in called functions
	sim_initSim();		// initialise simulation run-time environment
	initOS();		// initialise operating system
	logGeneric("Starting stimulus-based simulation");
	coreLoop();		// start scheduling loop
	logGeneric("Simulation complete, shutting down");
	sim_closeSim();		// shut down simulation envoronment
	fflush(stdout);			// make sure the output on the console is complete 
	//testBlockAddRemove();
	//testReadyAddRemove();
	system("pause");
	return 1; 
}