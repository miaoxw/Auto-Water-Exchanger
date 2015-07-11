#include <arduino.h>
#include <TimerOne.h>
#include "system_state.h"
#include "equipment.h"
#include "storage.h"

namespace Timer
{
	static long tickCount;
	static long countdownBase=800000;				//��ˮ�����ڣ�����604800��һ�ܣ���Ϊ��Ч

	static int periodicalTickCount;
	static const int periodicalCountdownBase = 300;		//�����Ի�ˮ����300�룿

	void timerISR();

	void setChangeWaterTime(long sec);
}

void Timer::init(long deltaTime)
{
	Timer1.initialize(10000000L);						//ÿ��һ�ε��жϣ���Ӳ�������޷�ʹ�÷���Ϊ���ڵ�λ
	//��������
	setChangeWaterTime(Storage::readlong(Storage::COUNTDOWNBASE_ADDRESS));
	Timer1.attachInterrupt(timerISR);
}

void Timer::setChangeWaterTime(long sec)
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