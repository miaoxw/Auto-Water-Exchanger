#include "decision.h"
#include "ph.h"
#include "timer.h"
#include "dht22.h"
#include "ports.h"
#include "equipment.h"
#include "water_sensor.h"
#include "system_state.h"

using Ports::FISH_TANK_PUMP;
using Ports::TAP_WATER_PUMP;
using Ports::DEWATERING_PUMP;

using namespace SystemState;

void setup()
{
	//Serial.begin(115200);
	pinMode(FISH_TANK_PUMP, OUTPUT);
	pinMode(TAP_WATER_PUMP, OUTPUT);
	pinMode(DEWATERING_PUMP, OUTPUT);

	/*按需使用中断
	attachInterrupt(0, Pump::fishTankPumpOn, RISING);
	attachInterrupt(1, Pump::fishTankPumpOn, RISING);
	attachInterrupt(2, Pump::fishTankPumpOn, RISING);
	attachInterrupt(3, Pump::fishTankPumpOn, RISING);
	attachInterrupt(4, Pump::fishTankPumpOn, RISING);
	attachInterrupt(5, Pump::fishTankPumpOn, RISING);
	*/

	dht22::init();
	Timer::init();
}

void loop()
{
	temperature = (char)round(dht22::getTemperature());
	fishTankFull = water_sensor::isFishTankOverflow();
	waterTankFull = water_sensor::isWaterTankOverflow();
	isWaterQualified = Ph::isWaterQualified();

	Decision::waterTankDecision[waterTankFull][isChangingWater]();
	Decision::fishTankDecision[isManualChanging][isPeriodicalChaningWater][fishTankFull][isWaterQualified]();
	Decision::tempratureControlDecision[temperature > 28][temperature < 24]();
}
