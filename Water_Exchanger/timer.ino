#include <arduino.h>
#include <TimerOne.h>
#include "system_state.h"
#include "equipment.h"
#include "storage.h"

using namespace Storage;

namespace Timer
{
	static long tickCount;
	static long countdownBase=800000;				//换水的周期，大于604800（一周）视为无效

	static int periodicalTickCount;
	static const int periodicalCountdownBase = 300;		//周期性换水持续300秒？

	void timerISR();

	void setChangeWaterTime(long sec);
}

void Timer::init(long deltaTime)
{
	Timer1.initialize(10000000L);						//每秒一次的中断，受硬件限制无法使用分钟为周期单位
	//读入设置
	setChangeWaterTime(readlong(StorageAddress(COUNTDOWN_BASE_ADDRESS)));
	Timer1.attachInterrupt(timerISR);
}

void Timer::setChangeWaterTime(long sec)
{
	countdownBase = sec;
	//修改定时时间后重新开始计时
	tickCount = countdownBase;
}

void Timer::timerISR()
{
	if (countdownBase <= 604800&&!SystemState::isManualChanging)				//有效参数，且换水不在被手动控制
	{
		tickCount--;
		if (tickCount <= 0)
		{
			tickCount = countdownBase;
			if (!SystemState::isChangingWater)	//不在换水才继续
			{
				periodicalTickCount = periodicalCountdownBase;
				SystemState::isPeriodicalChaningWater = true;
				SystemState::isChangingWater = true;
				periodicalTickCount = periodicalCountdownBase + 1;			//重置一个计时器
				Equipment::fishTankPumpOn();
				Serial.write("Start changing\n");
			}
		}

		periodicalTickCount--;
		if (periodicalTickCount < -1)
			periodicalTickCount = -1;
		if (periodicalTickCount==0)			//换水持续时间结束
		{
			SystemState::isPeriodicalChaningWater = false;
			SystemState::isChangingWater = false;
			Equipment::fishTankPumpOff();
			periodicalTickCount = -1;		//恢复此计时器到停用状态
			Serial.write("Changing finished\n");
		}
	}
}