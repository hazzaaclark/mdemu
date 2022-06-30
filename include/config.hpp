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


/***
* This is declared in the rare event that the Z80 and 68000 
* include DMA Corruption while computing with the Bus
*/

#define Z80_DMA_TRANSFER 1

/***
* This is to prevent any potential corruption bugs with accessing the IO Ports from the Bus
* MD MK2 includes an issue in which accessing the IO Data Lines from the Bus causes the computation between the 68000 and Z80 to corrupt. 
*/

#define Z80_IO_TRANSFER 1

/***
* In the event that you want to disable any Direct Memory Access between the Data & Address Lines
*/

#define DMA_DISABLED 0

/***
* This is to disable the Direct Memory Access computing with the Bus
* This is in the event of the Mem Banks being accessed by the Mapper
* From which, all of the Internal BIN Data from the CPU and Bus will correspond with the Mapper
*/

#define MEMBANK_SWITCH 0

#endif CONFIG