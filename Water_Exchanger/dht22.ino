#include <DHT.h>
#include "ports.h"

namespace dht22
{
	dht DHT;

	void init()
	{
		delay(3000);
	}

	float getTemperature()
	{
		int chk=DHT.read22(Ports::DHT22_PIN);
		if (chk != DHTLIB_OK)
			return 0.0/0;
		else
			return DHT.temperature;
	}
}
