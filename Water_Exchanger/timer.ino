#include <arduino.h>
#include <TimerOne.h>
#include "system_state.h"
#include "pump.h"

namespace Timer
{
	static int tickCount;
	static int countdownBase=10000000;				//��ˮ�����ڣ�����604800��һ�ܣ���Ϊ��Ч

	static int periodicalTickCount;
	static int periodicalCountdownBase = 300;		//�����Ի�ˮ����300�룿

	void timerISR();

	void setChangeWaterTime(int sec);
}

void Timer::init()
{
	Timer1.initialize(1000000);						//ÿ��һ�ε��жϣ���Ӳ�������޷�ʹ�÷���Ϊ���ڵ�λ
	Timer1.attachInterrupt(timerISR);
}

void Timer::setChangeWaterTime(int sec)
{
	countdownBase = sec;
	//�޸Ķ�ʱʱ������¿�ʼ��ʱ
	tickCount = 0;
}

void Timer::timerISR()
{
	if (countdownBase <= 604800)				//��Ч����
	{
		tickCount--;
		if (tickCount <= 0)
		{
			tickCount = countdownBase;
			if (!SystemState::isChangingWater)	//���ڻ�ˮ�ż���
			{
				periodicalTickCount = periodicalCountdownBase;
				SystemState::isPeriodicalChaningWater = true;
				periodicalTickCount = periodicalCountdownBase;			//����һ����ʱ��
				Pump::fishTankPumpOn();
			}
		}

		periodicalTickCount--;
		if (periodicalTickCount < -1)
			periodicalTickCount = -1;
		if (periodicalTickCount==0)			//��ˮ����ʱ�����
		{
			SystemState::isPeriodicalChaningWater = false;
			Pump::fishTankPumpOff();
			periodicalTickCount = -1;		//�ָ��˼�ʱ����ͣ��״̬
		}
	}
}