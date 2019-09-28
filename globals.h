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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

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

#define LOW_DIGIT(x) ((x) & 0xf)
#define HIGH_DIGIT(x) (((x) >> 4) & 0xf)
#define LOW_REGISTER(x) ((x) & 0xff)
#define HIGH_REGISTER(x) (((x) >> 8) & 0xff)

#define SET_LOW_REGISTER(x, v) x = (((x) & 0xff00) | ((v) & 0xff))
#define SET_HIGH_REGISTER(x, v) x = (((x) & 0xff) | (((v) & 0xff) << 8))

#define WORD16(x) ((x) & 0xffff)

/* CP/M memory definitions */
#define RAM_FAST // If this is defined, all RAM function calls become direct access (see below)
#define MEMSIZE 64 * 1024 // RAM(plus ROM) needs to be 64K to avoid compatibility issues

#ifdef RAM_FAST // Makes all function calls to memory access into direct RAM access (less calls / less code)
static uint8_t RAM[MEMSIZE];
#define _RamSysAddr(a)		&RAM[a]
#define _RamRead(a)			RAM[a]
#define _RamRead16(a)		((RAM[(a & 0xffff) + 1] << 8) | RAM[a & 0xffff])
#define _RamWrite(a, v)		RAM[a] = v
#define _RamWrite16(a, v)	RAM[a] = (v) & 0xff; RAM[a + 1] = (v) >> 8
#endif

#define tohex(x)	((x) < 10 ? (x) + 48 : (x) + 87)

#endif
