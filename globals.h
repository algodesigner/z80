#ifndef GLOBALS_H
#define GLOBALS_H

/* Some definitions needed globally */
#ifdef __MINGW32__
#include <ctype.h>
#endif

/* Definitions for file/console based debugging */
#define DEBUG
//#define DEBUGLOG		// Writes extensive call trace information to RunCPM.log
//#define CONSOLELOG	// Writes debug information to console instead of file
//#define LOGONLY 22	// If defined will log only this BDOS (or BIOS) function
//#define iDEBUG		// Instruction debugger (PC only, for development)

/* Some environment and type definitions */

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

typedef signed char     int8;
typedef signed short    int16;
typedef signed int      int32;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

#define LOW_DIGIT(x)            ((x) & 0xf)
#define HIGH_DIGIT(x)           (((x) >> 4) & 0xf)
#define LOW_REGISTER(x)         ((x) & 0xff)
#define HIGH_REGISTER(x)        (((x) >> 8) & 0xff)

#define SET_LOW_REGISTER(x, v)  x = (((x) & 0xff00) | ((v) & 0xff))
#define SET_HIGH_REGISTER(x, v) x = (((x) & 0xff) | (((v) & 0xff) << 8))

#define WORD16(x)	((x) & 0xffff)

/* CP/M memory definitions */
#define RAM_FAST	// If this is defined, all RAM function calls become direct access (see below)
					// This saves about 2K on the Arduino code and should bring speed improvements

#define MEMSIZE 64 * 1024	// RAM(plus ROM) needs to be 64K to avoid compatibility issues

#ifdef RAM_FAST		// Makes all function calls to memory access into direct RAM access (less calls / less code)
static uint8 RAM[MEMSIZE];
#define _RamSysAddr(a)		&RAM[a]
#define _RamRead(a)			RAM[a]
#define _RamRead16(a)		((RAM[(a & 0xffff) + 1] << 8) | RAM[a & 0xffff])
#define _RamWrite(a, v)		RAM[a] = v
#define _RamWrite16(a, v)	RAM[a] = (v) & 0xff; RAM[a + 1] = (v) >> 8
#endif

#define tohex(x)	((x) < 10 ? (x) + 48 : (x) + 87)

#endif
