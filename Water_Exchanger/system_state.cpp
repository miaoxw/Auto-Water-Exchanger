#include "system_state.h"

/**
 *������������ó�ʼֵӦ���趨Ϊ����ʹϵͳ�����κβ�����ֵ��
 *���е�ʱϵͳ����״̬����������Ӧ��ϵͳ�������иı������
 */

//Global state
bool SystemState::isManualChanging = false;
bool SystemState::isPeriodicalChaningWater = false;
bool SystemState::isChangingWater = false;

//Fish tank
char SystemState::temperature;
bool SystemState::fishTankFull = true;
bool SystemState::isWaterQualified = true;

//Water tank
bool SystemState::waterTankFull = true;



