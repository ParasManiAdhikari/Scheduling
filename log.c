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

void logPidCompleteness(unsigned pid, unsigned done, unsigned length,
	char* message)
{
	printf("%6u : PID %3u : completeness: %u/%u | %s\n", systemTime,
		pid, done, length, message);
}


void addReadyMessage(unsigned pid)
{
	printf("%6u : PID %3u: Added to the ready list\n", systemTime, pid);
}

void RemoveReadyMessage(unsigned pid)
{
	printf("%6u : PID %3u: Removed from the ready list\n", systemTime, pid);
}

void addBlockedMessage(unsigned pid, schedulingEvent_t reason)
{
	printf("%6u : PID %3u: Added to the blocked list : Event: %s\n", systemTime, pid, eventString[reason]);
}

void removeBlockedMessage(unsigned pid)
{
	printf("%6u : PID %3u : Removed from blocked list\n", pid, systemTime);
}

/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */



