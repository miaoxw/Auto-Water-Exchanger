#include "pump.h"
#include "ports.h"
#include <arduino.h>

using namespace Ports;

void Pump::fishTankPumpOn()
{
	digitalWrite(FISH_TANK_PUMP,LOW);
}

void Pump::fishTankPumpOff()
{
	digitalWrite(FISH_TANK_PUMP,HIGH);
}
