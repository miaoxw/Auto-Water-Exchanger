#include "decision.h"
#include "ph.h"
#include "timer.h"
#include "dht22.h"
#include "ports.h"
#include "equipment.h"
#include "water_sensor.h"
#include "system_state.h"
#include "ultrasonic.h"

using Ports::DHT22_PIN;
using Ports::FISH_TANK_PUMP;
using Ports::TAP_WATER_PUMP;
using Ports::DEWATERING_PUMP;
using Ports::FAN;
using Ports::HEATER;
using Ports::OXYGEN_PUMP;
using Ports::ULTRASONIC_ECHO;
using Ports::ULTRASONIC_TRIG;

using namespace SystemState;

int count = 1;

void setup()
{
	Serial.begin(115200);

	pinMode(DHT22_PIN, INPUT);
	pinMode(FISH_TANK_PUMP, OUTPUT);
	pinMode(TAP_WATER_PUMP, OUTPUT);
	pinMode(DEWATERING_PUMP, OUTPUT);
	pinMode(FAN, OUTPUT);
	pinMode(HEATER, OUTPUT);
	pinMode(OXYGEN_PUMP, OUTPUT);
	pinMode(ULTRASONIC_TRIG, OUTPUT);
	pinMode(ULTRASONIC_ECHO, INPUT);

	//按键部分的ISR按需使用
	//attachInterrupt(0, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(1, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(2, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(3, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(4, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(5, Equipment::fishTankPumpOn, RISING);

	dht22::init();
	//Timer::init();

	//氧气泵常开
	Equipment::oxygenPumpOn();
}

void loop()
{
	Serial.print("loop ");
	Serial.println(count++, DEC);
	float newTemprature = dht22::getTemperature();
	if (!isnan(newTemprature))
		temperature = newTemprature;
	//fishTankFull = WaterSensor::isFishTankOverflow();
	//waterTankFull = Ultrasonic::getDistance() < 5.0;
	//isWaterQualified = true;//Ph::isWaterQualified();

	Serial.print("Temprature:");
	Serial.println(newTemprature);
	//Serial.print("Fish tank:");
	//Serial.println(fishTankFull?"Full":"Not full");
	//Serial.print("Fish tank water quality:");
	//Serial.println(isWaterQualified ? "Good" : "Bad");
	//Serial.print("Water tank:");
	//Serial.println(waterTankFull ? "Full" : "Not full");

	//Decision::waterTankDecision[waterTankFull][isChangingWater]();
	//Decision::fishTankDecision[isManualChanging][isPeriodicalChaningWater][fishTankFull][isWaterQualified]();
	//Decision::tempratureControlDecision[temperature > 28][temperature < 24]();
}
