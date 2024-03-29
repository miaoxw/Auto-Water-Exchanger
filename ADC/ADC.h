#ifndef _ADC_h
#define _ADC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace AnalogDigitalConverter
{
	static const int INPUT_THRESHOLD[] = { 50, 200, 400, 600, 800 };
	static const int OUTPUT_VALUE[] = { 30, 150, 300, 500, 700, 900 };
	static const int NUM_KEYS = 5;

	int translateToKeyCode(unsigned int input);
}

#endif

