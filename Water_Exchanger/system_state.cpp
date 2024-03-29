#include "system_state.h"

/**
 *这里的所有设置初始值应当设定为不会使系统进行任何操作的值，
 *所有到时系统运行状态变更的情况都应由系统在运行中改变参数。
 */

//Global state
bool SystemState::isManualChanging = false;
bool SystemState::isPeriodicalChaningWater = false;
bool SystemState::isChangingWater = false;

//Fish tank
float SystemState::temperature;
bool SystemState::fishTankFull = true;
bool SystemState::isWaterQualified = true;

//Water tank
bool SystemState::waterTankFull = true;

int SystemState::light_state = 0;
int SystemState::water_state = 0;
int SystemState::oxygen_state = 1;
int SystemState::heat_state = 0;
int SystemState::automate_state = 0;
int SystemState::heat_temperature = 28;



