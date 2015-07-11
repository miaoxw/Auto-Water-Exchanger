#ifndef STORAGE_h
#define STORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

namespace Storage
{
	static const int COUNTDOWNBASE_ADDRESS = 0;		//4 Byte

	char readChar(int address);
	void writechar(int address, char content = '\0');
	int readint(int address);
	void writeint(int address, int content = 0);
	long readlong(int address);
	void writelong(int address, long content = 0);
}

#endif

