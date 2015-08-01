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
#include "input.h"
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
using namespace Equipment;

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
	Serial.println("pinMode OK");

	//关闭所有设备
	fishTankPumpOff();
	tapWaterPumpOff();
	dewateringPumpOff();
	Serial.println("All pumps turned off");

	Input::init();

	//避免ADC初始化时产生的多余信号
	delay(1000);

	//按键部分的ISR按需使用
	attachInterrupt(0, Interrupt::getKey, RISING);
	//attachInterrupt(1, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(2, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(3, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(4, Equipment::fishTankPumpOn, RISING);
	//attachInterrupt(5, Equipment::fishTankPumpOn, RISING);
	Serial.println("Interrupt set");

	dht22::init();
	//Timer::init();

	//氧气泵常开
	Equipment::oxygenPumpOn();

	//Watchdog
	wdt_enable(TIMEOUT);
	Serial.println("Initialization finished");
}

void loop()
{
	wdt_disable();
	float newTemprature = dht22::getTemperature();
	if (!isnan(newTemprature))
		temperature = newTemprature;
	wdt_enable(TIMEOUT);
	fishTankFull = WaterSensor::isFishTankOverflow();
	wdt_reset();
	waterTankFull = WaterSensor::isWaterTankOverflow();
	wdt_reset();
	isWaterQualified = Ph::isWaterQualified();
	wdt_reset();

	Serial.print("Temprature:");
	Serial.print(temperature, 1);
	Serial.println(" degrees C");
	Serial.print("Fish tank:");
	Serial.println(fishTankFull?"Full":"Not full");
	Serial.print("Fish tank water quality:");
	Serial.println(isWaterQualified ? "Good" : "Bad");
	Serial.print("Water tank:");
	Serial.println(waterTankFull ? "Full\n\n" : "Not full\n\n");

	if (!SystemState::isManualChanging)
	{
		Decision::waterTankDecision[waterTankFull][isChangingWater]();
		wdt_reset();
		Decision::fishTankDecision[isManualChanging][isPeriodicalChaningWater][fishTankFull][isWaterQualified]();
		wdt_reset();
		Decision::tempratureControlDecision[temperature > 28][temperature < 24]();
		wdt_reset();
	}

	//喂狗
	wdt_reset();
}
