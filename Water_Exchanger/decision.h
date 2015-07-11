#ifndef _DECISION_h
#define _DECISION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Decision
{
	extern void (*waterTankDecision[2][2])();
	extern void (*fishTankDecision[2][2][2][2])();
	extern void (*tempratureControlDecision[2][2])();
}

#endif

