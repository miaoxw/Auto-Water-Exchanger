#ifndef _PH_h
#define _PH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Ph
{
	bool isWaterQualified();
}

#endif

