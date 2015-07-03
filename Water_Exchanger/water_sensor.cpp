#include "water_sensor.h"
bool water_sensor::is_overflow(){
	int val = analogRead(water_sensor::water_sensor_pin);
	//Serial.print(val);
	if (val>100){
		//Serial.print("warning!!!\n");
		return 1;
	}
	else{
		//Serial.print("normal!!!\n");
		return 0;
	}
}