#ifndef _SYSTEM_STATE_h
#define _SYSTEM_STATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace SystemState
{
	extern bool isManualChanging;
	extern char temperature;
	extern bool full;
	extern bool isPeriodicalChaningWater;
	extern bool isChangingWater;
}

#endif

