#ifndef CONFIG
#define CONFIG

/***
* Memory Logs
* This is to define specific Memory Log allocations for both 68000 and Z80 CPU's
* There is probably a less roundabout way of achieving this allocation
*/

#define LOG_DISABLE 0
#define LOG_ERROR 1
#define LOG_WARNING 2
#define LOG_INFO 3
#define LIB_LOG LOG_WARNING

/***
* Oscillate between 1 and 0 to log errors as Mem Allocation
*/ 

#if (DEBUG != 0)
#define LIB_DEBUG 1

#else
#define LIB_DEBUG 0
#undef LIB_LOG
#define LIB_LOG LOG_WARNING
#endif
