#ifndef PORTS_H
#define PORTS_H

#define ANALOG		//�������Ƿ�����
#define DIGITAL		//�������Ƿ�����
#define PWM
#define IN
#define OUT
#define PROHIBITED(anything)	//����ԭ��ͨ������ʹ����ĳЩ�⣬��Щ�˿��޷��������������������Ԥ���������������ٴ洢����

namespace Ports
{
	//ģ��˿�
	ANALOG IN static const char FISHTANK_WATER_SENSOR = 1;
	ANALOG IN static const char WATERTANK_WATER_SENSOR = 2;
	ANALOG IN static const char PH_METER = 3;

	//���ֶ˿�
	PROHIBITED(DIGITAL static const char BY_INT_0 = 2;)
	PROHIBITED(DIGITAL static const char BY_INT_1 = 3;)
	DIGITAL OUT static const char FISH_TANK_PUMP = 7;
	DIGITAL OUT static const char TAP_WATER_PUMP = 8;
	DIGITAL OUT static const char DEWATERING_PUMP = 9;
	DIGITAL OUT static const char FAN = 10;
	PROHIBITED(PWM static const char BY_TIMERONE_1 = 11;)
	PROHIBITED(PWM static const char BY_TIMERONE_2 = 12;)
	PROHIBITED(PWM static const char BY_TIMERONE_3 = 13;)
	DIGITAL OUT static const char HEATER = 14;
	DIGITAL OUT static const char OXYGEN_PUMP = 15;
	DIGITAL OUT static const char ULTRASONIC_TRIG = 16;
	DIGITAL IN static const char ULTRASONIC_ECHO = 17;
	PROHIBITED(DIGITAL static const char BY_INT_5 = 18;)
	PROHIBITED(DIGITAL static const char BY_INT_4 = 19;)
	PROHIBITED(DIGITAL static const char BY_INT_3 = 20;)
	PROHIBITED(DIGITAL static const char BY_INT_2 = 21;)
}
#endif
