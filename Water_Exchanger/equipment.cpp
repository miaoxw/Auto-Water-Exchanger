#include "equipment.h"
#include "ports.h"
#include "system_state.h"
#include <arduino.h>

using namespace Ports;

void Equipment::tapWaterPumpOn()
{
	digitalWrite(TAP_WATER_PUMP, LOW);
}

void Equipment::tapWaterPumpOff()
{
	digitalWrite(TAP_WATER_PUMP, HIGH);
}

void Equipment::fishTankPumpOn()
{
	digitalWrite(FISH_TANK_PUMP, LOW);
}

void Equipment::fishTankPumpOff()
{
	digitalWrite(FISH_TANK_PUMP, HIGH);
}

void Equipment::dewateringPumpOn()
{
	digitalWrite(DEWATERING_PUMP, LOW);
}

void Equipment::dewateringPumpOff()
{
	digitalWrite(DEWATERING_PUMP, HIGH);
}

void Equipment::fanOn()
{
	digitalWrite(FAN, LOW);
}

void Equipment::fanOff()
{
	digitalWrite(FAN, HIGH);
}

void Equipment::heaterOn()
{
	digitalWrite(HEATER, LOW);
}

void Equipment::heaterOff()
{
	digitalWrite(HEATER, HIGH);
}

void Equipment::oxygenPumpOn()
{
	digitalWrite(OXYGEN_PUMP, LOW);
}

void Equipment::oxygenPumpOff()
{
	digitalWrite(OXYGEN_PUMP, HIGH);
}