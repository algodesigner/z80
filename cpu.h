/*
 * MIT License
 *
 * Copyright (c) 2017 Mockba the Borg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "globals.h"
#include "console.h"

typedef struct {
    int32_t pcx; /* external view of PC                          */
    int32_t af;  /* AF register                                  */
    int32_t bc;  /* BC register                                  */
    int32_t de;  /* DE register                                  */
    int32_t hl;  /* HL register                                  */
    int32_t ix;  /* IX register                                  */
    int32_t iy;  /* IY register                                  */
    int32_t pc;  /* program counter                              */
    int32_t sp;  /* SP register                                  */
    int32_t af1; /* alternate AF register                        */
    int32_t bc1; /* alternate BC register                        */
    int32_t de1; /* alternate DE register                        */
    int32_t hl1; /* alternate HL register                        */
    int32_t iff; /* Interrupt Flip Flop                          */
    int32_t ir;  /* Interrupt (upper) / Refresh (lower) register */

    int32_t status; /* Status of the CPU 0=running 1=end request 2=back to CCP */
    int32_t debug;
    int32_t brk;
    int32_t step;

#if defined(DEBUG) || defined(iDEBUG)
    int32_t watch;
#endif

#ifdef iDEBUG
    FILE *iLogFile;
    char iLogBuffer[16];
    const char *iLogTxt;
#endif

} z80;

#define PCX cpu->pcx
#define AF cpu->af
#define BC cpu->bc
#define DE cpu->de
#define HL cpu->hl
#define IX cpu->ix
#define IY cpu->iy
#define PC cpu->pc
#define SP cpu->sp
#define AF1 cpu->af1
#define BC1 cpu->bc1
#define DE1 cpu->de1
#define HL1 cpu->hl1
#define IFF cpu->iff
#define IR cpu->ir

/*
	Functions needed by the soft CPU implementation
*/
void cpu_out(z80 *cpu, const uint32_t Port, const uint32_t Value);

uint32_t cpu_in(z80 *cpu, const uint32_t Port);

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

#define SETFLAG(f,c) (AF = (c) ? AF | FLAG_ ## f : AF & ~FLAG_ ## f)
#define TSTFLAG(f) ((AF & FLAG_ ## f) != 0)

#define PARITY(x)   parityTable[(x) & 0xff]

#define SET_PVS(s)  (((cbits >> 6) ^ (cbits >> 5)) & 4)
#define SET_PV      (SET_PVS(sum))
#define SET_PV2(x)  ((temp == (x)) << 2)

#define POP(x)  {                          \
    register uint32_t y = RAM_PP(SP);      \
    x = y + (RAM_PP(SP) << 8);             \
}

#define JPC(cond) {                        \
    if (cond) {                            \
        PC = GET_WORD(PC);                 \
    } else {                               \
        PC += 2;                           \
    }                                      \
}

#define CALLC(cond) {                           \
    if (cond) {                                 \
        register uint32_t adrr = GET_WORD(PC);  \
        PUSH(PC + 2);                           \
        PC = adrr;                              \
    } else {                                    \
        PC += 2;                                \
    }                                           \
}

#endif

z80 *z80_new();
void Z80reset(z80 *cpu);
void z80_debug(z80 *cpu);
void z80_run(z80 *cpu);
void Z80_destroy(z80 *cpu);

