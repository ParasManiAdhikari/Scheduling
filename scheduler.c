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
    int quantum = 0;
    while (1) {
        int process_complete = 1;
        for (int i = 0; i < readyList; i++) {
            if (processTable[i].duration > 0) {
                process_complete = 0;
                processTable[i].duration--;
                quantum++;
                if (quantum == QUANTUM || processTable[i].duration == 0) {
                    quantum = 0;
                }
            }
        }
        if (process_complete) {
            break;
        }
    }
	return nextToRun;
}
	
/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




