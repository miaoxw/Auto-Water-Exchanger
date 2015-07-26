#include "ph.h"
#include "ports.h"

//目前的调校下，基准值在480左右，倒一下醋，下降到430左右，再倒相同的量，下降到380左右，最终稳定在371附近
//这里猜想传感器对碱性到底灵敏度完全相同

bool Ph::isWaterQualified()
{
	//读一个值
	int value = analogRead(Ports::PH_METER);
	return value > 390 && value < 570;
}