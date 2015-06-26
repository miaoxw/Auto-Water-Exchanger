#include "ports.h"
#include "pump.h"

using Ports::FISH_TANK_PUMP;

void setup()
{
	pinMode(FISH_TANK_PUMP,OUTPUT);
}

void loop()
{
	Pump::fishTankPumpOn();
	delay(1000);
	Pump::fishTankPumpOff();
	delay(1000);
}
