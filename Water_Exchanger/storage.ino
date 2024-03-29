#include "storage.h"
#include <EEPROM.h>

char Storage::readChar(StorageAddress address)
{
	char ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writechar(StorageAddress address, char content)
{
	char oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}

int Storage::readint(StorageAddress address)
{
	int ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writeint(StorageAddress address, int content)
{
	int oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}

long Storage::readlong(StorageAddress address)
{
	long ret;
	EEPROM.get(address, ret);
	return ret;
}

void Storage::writelong(StorageAddress address, long content)
{
	long oldContent;
	EEPROM.get(address, oldContent);
	if (oldContent != content)
		EEPROM.put(address, content);
}
