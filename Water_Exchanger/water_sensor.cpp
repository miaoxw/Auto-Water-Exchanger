#include "water_sensor.h"
#include "ports.h"
#include <arduino.h>

using namespace Ports;

bool WaterSensor::isFishTankOverflow(){
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

bool WaterSensor::isWaterTankOverflow(){
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
