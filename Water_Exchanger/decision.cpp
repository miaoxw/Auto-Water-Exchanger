#include "equipment.h"
#include "system_state.h"

using namespace Equipment;
using namespace SystemState;

void waterTankIn()
{
	tapWaterPumpOn();
}

void waterTankStop()
{
	tapWaterPumpOff();
}

void fishTank_dummy()
{
	fishTankPumpOff();
	dewateringPumpOff();
	isChangingWater = false;
}

void fishTank_in()
{
	fishTankPumpOn();
	dewateringPumpOff();
	isChangingWater = true;
}

void fishTank_out()
{
	fishTankPumpOff();
	dewateringPumpOn();
	isChangingWater = true;
}

void fishTank_inout()
{
	fishTankPumpOn();
	dewateringPumpOn();
	isChangingWater = true;
}

void temperatureControl_heat()
{
	heaterOn();
	fanOff();
}

void temperatureControl_cooldown()
{
	heaterOff();
	fanOn();
}

void tempratureControl_dummy()
{
	heaterOff();
	fanOff();
}

namespace Decision
{

	//[isOverflow][isChangingWater]
	void (*waterTankDecision[2][2])() = {
			{ waterTankIn, waterTankStop },
			{ waterTankStop, waterTankStop }
	};

	//[isManuallyChanging][isPeriodicallyChangingWater][isOverflow][isWaterQualified]
	void (*fishTankDecision[2][2][2][2])() = {
		//isManuallyChangingWater==false
			{
				//isPeriodicallyChangingWater==false
				{
					//isOverflow==false
					{ fishTank_inout, fishTank_in },
					//isOverflow==true
					{ fishTank_inout, fishTank_out }
				},
				//isPeriodicallyChangingWater==true
				{
					//isOverflow==false
					{ fishTank_dummy, fishTank_dummy },
					//isOverflow==true
					{ fishTank_dummy, fishTank_dummy }
				}
			},
			//isManuallyChangingWater==true
			{
				//isPeriodicallyChangingWater==false
				{
					//isOverflow==false
					{ fishTank_dummy, fishTank_dummy },
					//isOverflow==true
					{ fishTank_dummy, fishTank_dummy }
				},
				//isPeriodicallyChangingWater==true
				{
					//isOverflow==false
					{ fishTank_dummy, fishTank_dummy },
					//isOverflow==true
					{ fishTank_dummy, fishTank_dummy }
				}
			}
	};

	//[isTooHigh][isTooLow]
	//NOTICE: waterTankDecision[true][true] is impossible to be called!!
	void (*tempratureControlDecision[2][2])() = {
			{ tempratureControl_dummy, temperatureControl_heat },
			{ temperatureControl_cooldown, tempratureControl_dummy }
	};
}