#include <DHT.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302) DHT 11 DHT 21

namespace dht22
{
	DHT dht(DHTPIN, DHTTYPE);

	void init()
	{
		dht.begin();
	}
	
	float getTemperature()
	{
		float t = dht.readTemperature();
		delay(2000);
		t = dht.readTemperature();
		if (isnan(t))
		{
			return -100;
		}
		return t;
	}
}
