/* Implementation of the scheduler */
/* for comments on the functions see the associated .h-file */

/* ----------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "scheduler.h"


/* ----------------------------------------------------------------- */
/*                Declarations of local helper functions             */



/* ----------------------------------------------------------------- */
/*                Externally available functions                     */
/* ----------------------------------------------------------------- */

pid_t schedule(readyList_t readyListParam)
{
	pid_t nextToRun;
	if (readyListParam == NULL) return NO_PROCESS;
	// get process from readylist
	nextToRun = readyListParam->pid;
	// remove selected process from ready list	
	readyList=NULL;			// for batch only one process can be in readylist 
							// -> simply delete entire list
	return nextToRun;
}
	
/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




