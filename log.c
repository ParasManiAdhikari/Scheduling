/* Implementation of the log functions */
/* for comments on the functions see the associated .h-file */
/* please extent if needed to suit the needs of logging added functionality */
/* ---------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "log.h"


/* ---------------------------------------------------------------- */
/*                Declarations of local helper functions            */

/* ---------------------------------------------------------------- */
/* Declarations of global variables visible only in this file 		*/
// array with strings associated to scheduling events for log outputs
char eventString[6][12] = { "none", "started", "completed", "io", "quantumOver", "unblocked" };

/* ---------------------------------------------------------------- */
/*                Externally available functions					*/
/* ---------------------------------------------------------------- */

void logGeneric(char* message)
{
	printf("%6u : %s\n", systemTime, message);
}

void logPid(unsigned pid, char* message)
{
	printf("%6u : PID %3u : %s\n", systemTime, pid, message);
}

void logPidEvent(unsigned pid, schedulingEvent_t reason, char* message)
{
	printf("%6u : PID %3u : Event: %s | %s\n", systemTime,
		pid, eventString[reason], message);
}

void logPidAddReady(unsigned pid) {
	//printf("----------------------------------------------------\n");
	printf("%6u : PID %3u : add to readylist\n", systemTime, pid);
	//printf("----------------------------------------------------\n");
}

void logPidRemoveReady(unsigned pid) {
	//printf("----------------------------------------------------\n");
	printf("%6u : PID %3u : Removed from readylist \n", systemTime, pid);
	//printf("----------------------------------------------------\n");
}

void logPidAddBlocked(unsigned pid, schedulingEvent_t reason) {
	//printf("----------------------------------------------------\n");
	printf("%6u : PID %3u : add to blockedlist : Event: %s \n", systemTime, pid, eventString[reason]);
	//printf("----------------------------------------------------\n");
}

void logPidRemoveBlocked(unsigned pid) {
	//printf("----------------------------------------------------\n");
	printf("%6u : PID %3u : Removed from blockedlist \n", systemTime, pid);
	//printf("----------------------------------------------------\n");
}

void logPidCompleteness(unsigned pid, unsigned done, unsigned length,
	char* message)
{
	printf("%6u : PID %3u : completeness: %u/%u | %s\n", systemTime,
		pid, done, length, message);
}


/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */



