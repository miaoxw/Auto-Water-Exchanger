#ifndef _SYSTEM_STATE_h
#define _SYSTEM_STATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace SystemState
{
	//Global state
	extern bool isManualChanging;
	extern bool isPeriodicalChaningWater;
	extern bool isChangingWater;

	//Fish tank
	extern float temperature;
	extern bool fishTankFull;
	extern bool isWaterQualified;
	
	//Water tank
	extern bool waterTankFull;

	extern int light_state;
	extern int water_state;
	extern int oxygen_state;
	extern int heat_state;
	extern int automate_state;
	extern int heat_temperature;
}

#endif

