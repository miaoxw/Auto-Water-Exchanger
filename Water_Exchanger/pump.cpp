#include "pump.h"
#include "ports.h"
#include "system_state.h"
#include <arduino.h>

using namespace Ports;
using namespace SystemState;

void Pump::fishTankPumpOn()
{
	digitalWrite(FISH_TANK_PUMP, LOW);
	isChangingWater = true;
}

void Pump::fishTankPumpOff()
{
	digitalWrite(FISH_TANK_PUMP, HIGH);
	isChangingWater = false;
}
