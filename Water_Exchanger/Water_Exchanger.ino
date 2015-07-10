#include "timer.h"
#include "dht22.h"
#include "ports.h"
#include "pump.h"
#include "water_sensor.h"
#include "system_state.h"

using Ports::FISH_TANK_PUMP;
using Ports::TAP_WATER_PUMP;
using Ports::DEWATERING_PUMP;

using SystemState::isManualChanging;
using SystemState::temperature;
using SystemState::full;

void(*fishTankDecision[2][2])() = {
		{ Pump::fishTankPumpOn, Pump::fishTankPumpOn },
		{ Pump::fishTankPumpOn, Pump::fishTankPumpOn }
};

void setup()
{
	pinMode(FISH_TANK_PUMP, OUTPUT);
	pinMode(TAP_WATER_PUMP, OUTPUT);
	pinMode(DEWATERING_PUMP, OUTPUT);

	attachInterrupt(0, Pump::fishTankPumpOn, RISING);
	attachInterrupt(1, Pump::fishTankPumpOn, RISING);
	attachInterrupt(2, Pump::fishTankPumpOn, RISING);
	attachInterrupt(3, Pump::fishTankPumpOn, RISING);
	attachInterrupt(4, Pump::fishTankPumpOn, RISING);
	attachInterrupt(5, Pump::fishTankPumpOn, RISING);
	dht22::init();
}

void loop()
{
	temperature = (char)round(dht22::getTemperature());
	full = water_sensor::is_overflow() ? 1 : 0;
	//Do something?
	fishTankDecision[temperature][full]();
}
