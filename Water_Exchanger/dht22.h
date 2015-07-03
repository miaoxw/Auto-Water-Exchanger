#include "DHT.h" //ÐèÒªinstall ¿â
#ifndef DHT22_H
#define DHT22_H
#endif
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302) DHT 11 DHT 21
namespace dht22{
	DHT dht(DHTPIN, DHTTYPE);
	void init();
	float getTemperature();
}
