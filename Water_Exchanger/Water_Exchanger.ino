#include "decision.h"
#include "ph.h"
#include "timer.h"
#include "dht22.h"
#include "ports.h"
#include "equipment.h"
#include "water_sensor.h"
#include "system_state.h"
#include "ultrasonic.h"
#include "interrupt.h"
#include <avr/wdt.h>

#define TIMEOUT WDTO_8S

using Ports::DHT22_PIN;
using Ports::INTERRUPT_DATA;
using Ports::FISH_TANK_PUMP;
using Ports::TAP_WATER_PUMP;
using Ports::DEWATERING_PUMP;
using Ports::FAN;
using Ports::HEATER;
using Ports::OXYGEN_PUMP;
using Ports::ULTRASONIC_ECHO;
using Ports::ULTRASONIC_TRIG;

using namespace SystemState;

void setup()
{
	Serial.begin(115200);

	pinMode(DHT22_PIN, INPUT);
	pinMode(INTERRUPT_DATA, INPUT);
	pinMode(FISH_TANK_PUMP, OUTPUT);
	pinMode(TAP_WATER_PUMP, OUTPUT);
	pinMode(DEWATERING_PUMP, OUTPUT);
	pinMode(FAN, OUTPUT);
	pinMode(HEATER, OUTPUT);
	pinMode(OXYGEN_PUMP, OUTPUT);
	pinMode(ULTRASONIC_TRIG, OUTPUT);
	pinMode(ULTRASONIC_ECHO, INPUT);

	//避免ADC初始化时产生的多余信号
	delay(1000);

	//按键部分的ISR按需使用
	attachInterrupt(0, Interrupt::getKey, RISING);
	//attachInterrupt(1, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(2, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(3, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(4, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(5, Equipment::fishTankPumpOn, RISING);

	dht22::init();
	Timer::init();

	//氧气泵常开
	Equipment::oxygenPumpOn();

	//Watchdog
	wdt_enable(TIMEOUT);
}

void loop()
{
	float newTemprature = dht22::getTemperature();
	if (!isnan(newTemprature))
		temperature = newTemprature;
	fishTankFull = WaterSensor::isFishTankOverflow();
	waterTankFull = WaterSensor::isWaterTankOverflow();
	isWaterQualified = Ph::isWaterQualified();

	Serial.print("Temprature:");
	Serial.print(temperature, 1);
	Serial.println(" degrees C");
	Serial.print("Fish tank:");
	Serial.println(fishTankFull?"Full":"Not full");
	Serial.print("Fish tank water quality:");
	Serial.println(isWaterQualified ? "Good" : "Bad");
	Serial.print("Water tank:");
	Serial.println(waterTankFull ? "Full" : "Not full");

	if (!SystemState::isManualChanging)
	{
		Decision::waterTankDecision[waterTankFull][isChangingWater]();
		Decision::fishTankDecision[isManualChanging][isPeriodicalChaningWater][fishTankFull][isWaterQualified]();
		Decision::tempratureControlDecision[temperature > 28][temperature < 24]();
	}

	//喂狗
	wdt_reset();
}
