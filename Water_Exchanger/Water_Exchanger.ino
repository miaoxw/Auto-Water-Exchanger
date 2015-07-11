#include "decision.h"
#include "ph.h"
#include "timer.h"
#include "dht22.h"
#include "ports.h"
#include "equipment.h"
#include "water_sensor.h"
#include "system_state.h"
#include "ultrasonic.h"

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
	pinMode(FAN, OUTPUT);
	pinMode(HEATER, OUTPUT);
	pinMode(OXYGEN_PUMP, OUTPUT);
	pinMode(ULTRASONIC_TRIG, OUTPUT);
	pinMode(ULTRASONIC_ECHO, INPUT);

	//����ʹ���жϣ����������ISRֻ��д��������ŵ�
	attachInterrupt(0, Equipment::fishTankPumpOn, RISING);
	attachInterrupt(1, Equipment::fishTankPumpOn, RISING);
	attachInterrupt(2, Equipment::fishTankPumpOn, RISING);
	attachInterrupt(3, Equipment::fishTankPumpOn, RISING);
	attachInterrupt(4, Equipment::fishTankPumpOn, RISING);
	attachInterrupt(5, Equipment::fishTankPumpOn, RISING);

	dht22::init();
	Timer::init();

	//�����ó���
	Equipment::oxygenPumpOn();
}

void loop()
{
	temperature = (char)round(dht22::getTemperature());
	fishTankFull = WaterSensor::isFishTankOverflow();
	waterTankFull = Ultrasonic::getDistance() < 5.0;
	isWaterQualified = Ph::isWaterQualified();

	Decision::waterTankDecision[waterTankFull][isChangingWater]();
	Decision::fishTankDecision[isManualChanging][isPeriodicalChaningWater][fishTankFull][isWaterQualified]();
	Decision::tempratureControlDecision[temperature > 28][temperature < 24]();
}
