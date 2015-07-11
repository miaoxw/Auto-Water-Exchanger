#include <arduino.h>
#include <TimerOne.h>
#include "system_state.h"
#include "equipment.h"

namespace Timer
{
	static int tickCount;
	static int countdownBase=800000;				//��ˮ�����ڣ�����604800��һ�ܣ���Ϊ��Ч

	static int periodicalTickCount;
	static int periodicalCountdownBase = 300;		//�����Ի�ˮ����300�룿

	void timerISR();

	void setChangeWaterTime(int sec);
}

void Timer::init(int deltaTime)
{
	Timer1.initialize(10000000UL);						//ÿ��һ�ε��жϣ���Ӳ�������޷�ʹ�÷���Ϊ���ڵ�λ
	setChangeWaterTime(720);
	periodicalCountdownBase = 300;
	Timer1.attachInterrupt(timerISR);
}

void Timer::setChangeWaterTime(int sec)
{
	countdownBase = sec;
	//�޸Ķ�ʱʱ������¿�ʼ��ʱ
	tickCount = countdownBase;
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
				periodicalTickCount = periodicalCountdownBase + 1;			//����һ����ʱ��
				Equipment::fishTankPumpOn();
				Serial.write("Start changing\n");
			}
		}

		periodicalTickCount--;
		if (periodicalTickCount < -1)
			periodicalTickCount = -1;
		if (periodicalTickCount==0)			//��ˮ����ʱ�����
		{
			SystemState::isPeriodicalChaningWater = false;
			Equipment::fishTankPumpOff();
			periodicalTickCount = -1;		//�ָ��˼�ʱ����ͣ��״̬
			Serial.write("Changing finished\n");
		}
	}
}