# put this file in the same dir with ports.h
# TODO: define pin in ports.cpp and ports.h

#include "tracking.h"
#include "ports.h"
#include <arduino.h>

using namespace Ports;

int Tracking::getLineColor()
{
	int val;//定义数字变量val
	delay(1000);
	val=digitalRead(TRACKING_PIN);//将数字接口3的值读取赋给val
	return val;
}
