#include "ADC.h"
#include "ports.h"
#include <avr/wdt.h>

using namespace Ports;
using namespace AnalogDigitalConverter;

static const int RESET_THRESHOLD = 100;

int oldKeyCode;

#define TIMEOUT WDTO_1S

void setup()
{
	pinMode(KEY_VALUE, OUTPUT);
	pinMode(OUTPUT_SIGNAL, OUTPUT);
	oldKeyCode = -1;
	wdt_enable(TIMEOUT);
}

void loop()
{
	unsigned int keyValue = analogRead(OTHER_KEYS);
	int keyCode = translateToKeyCode(keyValue);
	unsigned int resetValue = analogRead(RESET);
	if (keyCode < 0 && resetValue < RESET_THRESHOLD)
		keyCode = 5;

	if (keyCode != oldKeyCode)
	{
		if (keyCode>=0)
		{
			analogWrite(KEY_VALUE, map(OUTPUT_VALUE[keyCode], 0, 1023, 0, 255));
			delay(10);
			digitalWrite(OUTPUT_SIGNAL, HIGH);
			delay(100);
			digitalWrite(OUTPUT_SIGNAL, LOW);
		}
		oldKeyCode = keyCode;
	}
	wdt_reset();
}
