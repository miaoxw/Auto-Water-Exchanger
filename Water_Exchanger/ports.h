#ifndef PORTS_H
#define PORTS_H

#define ANALOG		//仅起助记符作用
#define DIGITAL		//仅起助记符作用
#define PROHIBITED(something)	//禁用原因通常是因使用了某些库，这些端口无法用于正常输出；将其在预处理中消除，减少存储开销

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
