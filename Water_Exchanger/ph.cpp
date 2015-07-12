#include "ph.h"
#include "ports.h"

bool Ph::isWaterQualified()
{
	//读一个值
	int value = analogRead(Ports::PH_METER);
	return value > 100 && value < 200;
}