#include "ph.h"
#include "ports.h"

bool Ph::isWaterQualified()
{
	//¶ÁÒ»¸öÖµ
	int value = analogRead(Ports::PH_METER);
	return value > 100 && value < 200;
}