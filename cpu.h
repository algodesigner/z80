#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "globals.h"
#include "console.h"

/* see main.c for definition */

int32_t PCX; /* external view of PC                          */
int32_t AF;  /* AF register                                  */
int32_t BC;  /* BC register                                  */
int32_t DE;  /* DE register                                  */
int32_t HL;  /* HL register                                  */
int32_t IX;  /* IX register                                  */
int32_t IY;  /* IY register                                  */
int32_t PC;  /* program counter                              */
int32_t SP;  /* SP register                                  */
int32_t AF1; /* alternate AF register                        */
int32_t BC1; /* alternate BC register                        */
int32_t DE1; /* alternate DE register                        */
int32_t HL1; /* alternate HL register                        */
int32_t IFF; /* Interrupt Flip Flop                          */
int32_t IR;  /* Interrupt (upper) / Refresh (lower) register */
int32_t Status; /* Status of the CPU 0=running 1=end request 2=back to CCP */
int32_t Debug;
int32_t Break;
int32_t Step;

#ifdef iDEBUG
FILE *iLogFile;
char iLogBuffer[16];
const char *iLogTxt;
#endif

/*
	Functions needed by the soft CPU implementation
*/
void cpu_out(const uint32_t Port, const uint32_t Value);

uint32_t cpu_in(const uint32_t Port);

/* Z80 Custom soft core */

/* simulator stop codes */
#define STOP_HALT       0   /* HALT                                             */
#define STOP_IBKPT      1   /* breakpoint   (program counter)                   */
#define STOP_MEM        2   /* breakpoint   (memory access)                     */
#define STOP_INSTR      3   /* breakpoint   (instruction access)                */
#define STOP_OPCODE     4   /* invalid operation encountered (8080, Z80, 8086)  */

#define ADDRMASK        0xffff

#define FLAG_C  1
#define FLAG_N  2
#define FLAG_P  4
#define FLAG_H  16
#define FLAG_Z  64
#define FLAG_S  128

#define SETFLAG(f,c)    (AF = (c) ? AF | FLAG_ ## f : AF & ~FLAG_ ## f)
#define TSTFLAG(f)      ((AF & FLAG_ ## f) != 0)

#define PARITY(x)   parityTable[(x) & 0xff]

#define SET_PVS(s)  (((cbits >> 6) ^ (cbits >> 5)) & 4)
#define SET_PV      (SET_PVS(sum))
#define SET_PV2(x)  ((temp == (x)) << 2)

#define POP(x)  {                               \
    register uint32_t y = RAM_PP(SP);             \
    x = y + (RAM_PP(SP) << 8);                  \
}

#define JPC(cond) {                             \
    if (cond) {                                 \
        PC = GET_WORD(PC);                      \
    } else {                                    \
        PC += 2;                                \
    }                                           \
}

#define CALLC(cond) {                           \
    if (cond) {                                 \
        register uint32_t adrr = GET_WORD(PC);    \
        PUSH(PC + 2);                           \
        PC = adrr;                              \
    } else {                                    \
        PC += 2;                                \
    }                                           \
}

#endif

void Z80reset(void);
void Z80debug(void);
void Z80run(void);

