#ifndef PORTS_H
#define PORTS_H

#define ANALOG		//�������Ƿ�����
#define DIGITAL		//�������Ƿ�����
#define PROHIBITED(something)	//����ԭ��ͨ������ʹ����ĳЩ�⣬��Щ�˿��޷��������������������Ԥ���������������ٴ洢����

namespace Ports
{
	ANALOG static const char WATER_SENSOR = 1;
	PROHIBITED(ANALOG static const char BY_TIMERONE_1 = 11;)
	PROHIBITED(ANALOG static const char BY_TIMERONE_2 = 12;)
	PROHIBITED(ANALOG static const char BY_TIMERONE_3 = 13;)
	DIGITAL static const char FISH_TANK_PUMP = 7;
	DIGITAL static const char TAP_WATER_PUMP = 8;
	DIGITAL static const char DEWATERING_PUMP = 9;
}
#endif
