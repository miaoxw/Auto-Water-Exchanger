#include <arduino.h>
#include <TimerOne.h>
#include "system_state.h"
#include "pump.h"

namespace Timer
{
	static int tickCount;
	static int countdownBase=10000000;				//换水的周期，大于604800（一周）视为无效

	static int periodicalTickCount;
	static int periodicalCountdownBase = 300;		//周期性换水持续300秒？

	void timerISR();

	void setChangeWaterTime(int sec);
}

void Timer::init()
{
	Timer1.initialize(1000000);						//每秒一次的中断，受硬件限制无法使用分钟为周期单位
	Timer1.attachInterrupt(timerISR);
}

void Timer::setChangeWaterTime(int sec)
{
	countdownBase = sec;
	//修改定时时间后重新开始计时
	tickCount = 0;
}

void Timer::timerISR()
{
	if (countdownBase <= 604800)				//有效参数
	{
		tickCount--;
		if (tickCount <= 0)
		{
			tickCount = countdownBase;
			if (!SystemState::isChangingWater)	//不在换水才继续
			{
				periodicalTickCount = periodicalCountdownBase;
				SystemState::isPeriodicalChaningWater = true;
				periodicalTickCount = periodicalCountdownBase;			//重置一个计时器
				Pump::fishTankPumpOn();
			}
		}

		periodicalTickCount--;
		if (periodicalTickCount < -1)
			periodicalTickCount = -1;
		if (periodicalTickCount==0)			//换水持续时间结束
		{
			SystemState::isPeriodicalChaningWater = false;
			Pump::fishTankPumpOff();
			periodicalTickCount = -1;		//恢复此计时器到停用状态
		}
	}
}