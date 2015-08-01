#ifndef _PORTS_h
#define _PORTS_h

#define ANALOG
#define DIGITAL
#define PWM
#define IN
#define OUT

namespace Ports
{
	//模拟端口
	ANALOG IN static const char OTHER_KEYS = 0;
	ANALOG IN static const char RESET = 2;

	//数字端口
	DIGITAL OUT PWM static const char KEY_VALUE = 11;
	DIGITAL OUT static const char OUTPUT_SIGNAL = 13;
}

#endif

