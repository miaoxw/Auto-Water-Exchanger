#include <DHT.h>

#ifndef DHT22_H
#define DHT22_H

namespace dht22
{
	extern DHT dht;
	void init();
	float getTemperature();
}

#endif
