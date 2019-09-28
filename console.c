#include <stdio.h>
#include "console.h"

unsigned char _getch(void) {
	return getchar();
}

void _putch(uint8_t ch) {
	putchar(ch);
}


uint8_t mask8bit = 0x7f;		// TO be used for masking 8 bit characters (XMODEM related)
							// If set to 0x7f, RunCPM masks the 8th bit of characters sent
							// to the console. This is the standard CP/M behavior.
							// If set to 0xff, RunCPM passes 8 bit characters. This is
							// required for XMODEM to work.
							// Use the CONSOLE7 and CONSOLE8 programs to change this on the fly.
/*
uint8_t _chready(void)		// Checks if there's a character ready for input
{
	return(_kbhit() ? 0xff : 0x00);
}

uint8_t _getchNB(void)		// Gets a character, non-blocking, no echo
{
	return(_kbhit() ? _getch() : 0x00);
}
*/
void _putcon(uint8_t ch)		// Puts a character
{
	_putch(ch & mask8bit);
}

void _puts(const char *str)	// Puts a \0 terminated string
{
	while (*str)
		_putcon(*(str++));
}

void _puthex8(uint8_t c)		// Puts a HH hex string
{
	_putcon(tohex(c >> 4));
	_putcon(tohex(c & 0x0f));
}

void _puthex16(uint16_t w)	// puts a HHHH hex string
{
	_puthex8(w >> 8);
	_puthex8(w & 0x00ff);
}
