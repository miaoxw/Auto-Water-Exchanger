#include "ADC.h"

using namespace AnalogDigitalConverter;

int AnalogDigitalConverter::translateToKeyCode(unsigned int value)
{
	for (int i = 0; i < NUM_KEYS; i++)
		if (value < INPUT_THRESHOLD[i])
			return i;
	return -1;
}
