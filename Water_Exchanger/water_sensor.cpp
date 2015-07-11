#include "water_sensor.h"
#include "ports.h"
#include <arduino.h>

using namespace Ports;

bool water_sensor::isFishTankOverflow(){
	int val = analogRead(FISHTANK_WATER_SENSOR);
	//Serial.print(val);
	if (val > 100)
	{
		//Serial.print("warning!!!\n");
		return true;
	}
	else
	{
		//Serial.print("normal!!!\n");
		return false;
	}
}

bool water_sensor::isWaterTankOverflow(){
	int val = analogRead(WATERTANK_WATER_SENSOR);
	//Serial.print(val);
	if (val > 100)
	{
		//Serial.print("warning!!!\n");
		return true;
	}
	else
	{
		//Serial.print("normal!!!\n");
		return false;
	}
}
