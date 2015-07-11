
#include "storage.h"
#include <eeprom.h>

char Storage::readChar(int address)
{
	char ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writechar(int address, char content)
{
	char oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}

int Storage::readint(int address)
{
	int ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writeint(int address, int content)
{
	int oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}

long Storage::readlong(int address)
{
	long ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writelong(int address, long content)
{
	long oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}