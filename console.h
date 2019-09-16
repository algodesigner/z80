#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include "globals.h"

unsigned char _getch(void);

void _putch(uint8 ch);

uint8 mask8bit;				// TO be used for masking 8 bit characters (XMODEM related)
							// If set to 0x7f, RunCPM masks the 8th bit of characters sent
							// to the console. This is the standard CP/M behavior.
							// If set to 0xff, RunCPM passes 8 bit characters. This is
							// required for XMODEM to work.
							// Use the CONSOLE7 and CONSOLE8 programs to change this on the fly.
/*
uint8 _chready(void)		// Checks if there's a character ready for input
{
	return(_kbhit() ? 0xff : 0x00);
}

uint8 _getchNB(void)		// Gets a character, non-blocking, no echo
{
	return(_kbhit() ? _getch() : 0x00);
}
*/
void _putcon(uint8 ch);		// Puts a character

void _puts(const char *str);	// Puts a \0 terminated string

void _puthex8(uint8 c);		// Puts a HH hex string

void _puthex16(uint16 w);	// puts a HHHH hex string

#endif
