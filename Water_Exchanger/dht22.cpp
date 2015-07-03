#include "DHT.h"
#include "dht22.h"
void dht22::init(){
	dht.begin();
}

float dht22::getTemperature(){
	float t = dht.readTemperature();
	delay(2000);
	t = dht.readTemperature();
	if (isnan(t)) {
		//Serial.println("Failed to read from DHT sensor!");
		return -100;
	}
	return t;
}