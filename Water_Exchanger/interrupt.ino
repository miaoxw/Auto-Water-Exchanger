#include "interrupt.h"
#include "ports.h"

static const unsigned int ADC_TRESHOLD = 10;

//
static const int KEY_VALUES[] = { 50, 200, 400, 600, 800, 1000 };

static int translateToKeyCode(unsigned int input)
{
	for (int i = 0; i < 6; i++)
		if (input < KEY_VALUES[i])
			return i;
	return -1;
}

void Interrupt::getKey()
{
	noInterrupts();
	unsigned int pulseHigh = pulseIn(Ports::INTERRUPT_DATA, HIGH);
	unsigned int pulseLow = pulseIn(Ports::INTERRUPT_DATA, LOW);
	unsigned int adcValue = 1023.0*pulseHigh / (pulseHigh + pulseLow);
	if (adcValue > ADC_TRESHOLD)	//Avoid noise
	{
		//do ISR according to the key
		int keyCode = translateToKeyCode(adcValue);
	}
	interrupts();
}
