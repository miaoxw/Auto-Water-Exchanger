#ifndef STORAGE_h
#define STORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define COUNTDOWN_BASE_ADDRESS 0

namespace Storage
{
	enum StorageAddress
	{
		countdownBaseAddress = 0,		//4 Byte
	};

	char readChar(StorageAddress address);
	void writechar(StorageAddress address, char content = '\0');
	int readint(StorageAddress address);
	void writeint(StorageAddress address, int content = 0);
	long readlong(StorageAddress address);
	void writelong(StorageAddress address, long content = 0);
}

#endif

