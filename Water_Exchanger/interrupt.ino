#include "interrupt.h"
#include "ports.h"
#include "input.h"
#include "equipment.h"

using Input::display;
using SystemState::automate_state;
using SystemState::heat_state;
using SystemState::light_state;
using SystemState::oxygen_state;
using SystemState::heat_temperature;
using Input::format_time;
using Input::light_start;
using Input::light_end;
using Input::oxygen_start;
using Input::oxygen_end;
using Input::water_time;
using Input::mapKey;
using namespace Equipment;

static const unsigned int ADC_TRESHOLD = 10;

static const unsigned int KEY_VALUES[] = { 50, 200, 400, 600, 800, 1000 };

static const int state_fsm[51][5] = {
		{ 2, 0, 0, 0, 0 },
		{ 5, 1, 4, 3, 0 },
		{ 6, 1, 2, 4, 0 },
		{ 7, 1, 3, 2, 0 },
		{ 10, 2, 13, 8, 0 },
		{ 19, 3, 18, 16, 0 },
		{ 15, 4, 0, 0, 0 },
		{ 9, 2, 5, 11, 0 },
		{ 9, 2, 5, 11, 0 },
		{ 10, 2, 13, 8, 0 },
		{ 12, 2, 8, 13, 0 },
		{ 12, 2, 8, 13, 0 },
		{ 14, 2, 11, 5, 0 },
		{ 14, 2, 11, 5, 0 },
		{ 15, 4, 0, 0, 0 },
		{ 21, 3, 6, 17, 0 },
		{ 22, 3, 16, 18, 0 },
		{ 24, 3, 17, 6, 0 },
		{ 20, 27, 25, 26, 27 },
		{ 6, 32, 30, 31, 32 },
		{ 16, 37, 35, 36, 37 },
		{ 23, 42, 40, 41, 42 },
		{ 17, 47, 45, 46, 47 },
		{ 18, 0, 50, 51, 0 },
		{ 20, 27, 25, 26, 27 },
		{ 20, 27, 25, 26, 27 },
		{ 20, 19, 28, 29, 19 },
		{ 20, 19, 28, 29, 19 },
		{ 20, 19, 28, 29, 19 },
		{ 6, 32, 30, 31, 32 },
		{ 6, 32, 30, 31, 32 },
		{ 6, 20, 33, 34, 20 },
		{ 6, 20, 33, 34, 20 },
		{ 6, 20, 33, 34, 20 },
		{ 16, 37, 35, 36, 37 },
		{ 16, 37, 35, 36, 37 },
		{ 16, 21, 38, 39, 21 },
		{ 16, 21, 38, 39, 21 },
		{ 16, 21, 38, 39, 21 },
		{ 23, 42, 40, 41, 42 },
		{ 23, 42, 40, 41, 42 },
		{ 23, 22, 43, 44, 22 },
		{ 23, 22, 43, 44, 22 },
		{ 23, 22, 43, 44, 22 },
		{ 17, 47, 45, 46, 47 },
		{ 17, 47, 45, 46, 47 },
		{ 17, 23, 48, 49, 23 },
		{ 17, 23, 48, 49, 23 },
		{ 17, 23, 48, 49, 23 },
		{ 18, 0, 50, 51, 0 },
		{ 18, 0, 50, 51, 0 },
};

static int oldstate;

static int translateToKeyCode(unsigned int input)
{
	for (int i = 0; i < 6; i++)
		if (input < KEY_VALUES[i])
			return i;
	return -1;
}

void Interrupt::getKey()
{
	noInterrupts();
	unsigned int pulseHigh = pulseIn(Ports::INTERRUPT_DATA, HIGH);
	unsigned int pulseLow = pulseIn(Ports::INTERRUPT_DATA, LOW);
	unsigned int adcValue = 1023.0 * pulseHigh / (pulseHigh + pulseLow);
	if (adcValue > ADC_TRESHOLD)	//Avoid noise
	{
		//do ISR according to the key
		unsigned int keyCode = mapKey(translateToKeyCode(adcValue));
		operateFSM(keyCode);
	}

	interrupts();
}

void Interrupt::operateFSM(unsigned int keyCode)
{
	int state = state_fsm[oldstate - 1][keyCode];
	if (state != 0)
	{
		display.clear();
		switch (state)
		{
		case 1:
			display.setCursor(0, 0);
			display.print("PH=7  25c       ");
			display.setCursor(0, 1);
			display.print("2015-7-15 12:00       ");
			break;

		case 2:
			display.setCursor(0, 0);
			display.print("Mode choice:          ");
			display.setCursor(0, 1);
			display.print("Immediately    ");
			break;

		case 3:
			display.setCursor(0, 0);
			display.print("Mode choice:          ");
			display.setCursor(0, 1);
			display.print("Period       ");
			break;

		case 4:
			display.setCursor(0, 0);
			display.print("Mode choice:          ");
			display.setCursor(0, 1);
			display.print("Automate       ");
			break;

		case 5:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			display.setCursor(0, 1);
			if (light_state == 0)
			{
				display.print("light off      ");
			}
			else if (light_state == 1)
			{
				display.print("light on      ");
			}
			else
			{
				display.print("light err 5     ");
			}
			break;

		case 6:
			display.setCursor(0, 0);
			display.print("Period      ");
			display.setCursor(0, 1);
			display.print("Set light      ");
			break;

		case 7:
			display.setCursor(0, 0);
			display.print("Automate      ");
			display.setCursor(0, 1);
			if (automate_state == 0)
			{
				display.print("Automate off    ");
			}
			else if (automate_state == 1)
			{
				display.print("Automate on    ");
			}
			else
			{
				display.print("Automate err 7    ");
			}
			break;

		case 8:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			display.setCursor(0, 1);
			display.print("Change Water?          ");
			break;

		case 9:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			display.setCursor(0, 1);
			display.print("Water changing...     ");
			//TODO
			manualChangeWaterStart();
			break;

		case 10:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			if (light_state == 0)
			{
				//TODO
				//open light
				light_state = 1;
				display.setCursor(0, 1);
				display.print("Light on     ");
			}
			else if (light_state == 1)
			{
				//TODO
				//close light
				light_state = 0;
				display.setCursor(0, 1);
				display.print("Light off     ");
			}
			else
			{
				display.setCursor(0, 1);
				display.print("Light err 10   ");
			}
			break;

		case 11:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			if (oxygen_state == 0)
			{
				display.setCursor(0, 1);
				display.print("Oxygen off     ");
			}
			else if (oxygen_state == 1)
			{
				display.setCursor(0, 1);
				display.print("Oxygen on     ");
			}
			else
			{
				display.setCursor(0, 1);
				display.print("Oxygen err 11    ");
			}
			break;

		case 12:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			if (oxygen_state == 0)
			{
				//TODO
				oxygen_state = 1;
				oxygenPumpOn();				
				display.setCursor(0, 1);
				display.print("Oxygen on     ");
			}
			else if (oxygen_state == 1)
			{
				//TODO
				oxygen_state = 0;
				oxygenPumpOff();
				display.setCursor(0, 1);
				display.print("Oxygen off     ");
			}
			else
			{
				display.setCursor(0, 1);
				display.print("Oxygen err 12     ");
			}
			break;

		case 13:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			display.setCursor(0, 1);
			if (heat_state == 0)
			{
				display.print("heat off     ");
			}
			else if (heat_state == 1)
			{
				display.print("heat on     ");
			}
			else
			{
				display.print("heat err 13     ");
			}
			break;

		case 14:
			display.setCursor(0, 0);
			display.print("Immediately      ");
			display.setCursor(0, 1);
			if (heat_state == 0)
			{
				//TODO
				heat_state = 1;
				heaterOn();
				display.print("heat on     ");
			}
			else if (heat_state == 1)
			{
				//TODO
				heat_state = 0;
				heaterOff();
				display.print("heat off       ");
			}
			else
			{
				display.print("heat err 14     ");
			}
			break;

		case 15:
			display.setCursor(0, 0);
			display.print("Automate      ");
			display.setCursor(0, 1);
			if (automate_state == 0)
			{
				automate_state = 1;
				display.print("Automate on");
			}
			else if (automate_state == 1)
			{
				automate_state = 0;
				display.print("Automate off");
			}
			else
			{
				display.print("Automate err 15  ");
			}
			break;

		case 16:
			display.setCursor(0, 0);
			display.print("Period      ");
			display.setCursor(0, 1);
			display.print("Set change water     ");
			break;

		case 17:
			display.setCursor(0, 0);
			display.print("Period      ");
			display.setCursor(0, 1);
			display.print("Set oxygen     ");
			break;

		case 18:
			display.setCursor(0, 0);
			display.print("Period      ");
			display.setCursor(0, 1);
			display.print("Set heat     ");
			break;

		case 19:
			display.setCursor(0, 0);
			display.print("Start(light)      ");
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 20:
			display.setCursor(0, 0);
			display.print("End(light)      ");
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 21:
			display.setCursor(0, 0);
			display.print("Time(water)      ");
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 22:
			display.setCursor(0, 0);
			display.print("Start(oxygen)      ");
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 23:
			display.setCursor(0, 0);
			display.print("End(oxygen)      ");
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 24:
			display.setCursor(0, 0);
			display.print("Temperature     ");
			display.setCursor(0, 1);
			display.print((int)SystemState::heat_temperature);
			break;

		case 25:
			display.setCursor(0, 0);
			display.print("Start(light)     ");
			light_start[0]++;
			if (light_start[0] == 24)
			{
				light_start[0] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 26:
			display.setCursor(0, 0);
			display.print("Start(light)     ");
			light_start[0]--;
			if (light_start[0] == -1)
			{
				light_start[0] = 23;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 27:
			//blink
			display.setCursor(0, 0);
			display.print("Start(light)     ");
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 28:
			display.setCursor(0, 0);
			display.print("Start(light)     ");
			light_start[1]++;
			if (light_start[1] == 60)
			{
				light_start[1] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 29:
			display.setCursor(0, 0);
			display.print("Start(light)     ");
			light_start[1]--;
			if (light_start[1] == -1)
			{
				light_start[1] = 59;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_start));
			break;

		case 30:
			display.setCursor(0, 0);
			display.print("End(light)     ");
			light_end[0]++;
			if (light_end[0] == 24)
			{
				light_end[0] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 31:
			display.setCursor(0, 0);
			display.print("End(light)     ");
			light_end[0]--;
			if (light_end[0] == -1)
			{
				light_end[0] = 23;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 32:
			//blink change
			display.setCursor(0, 0);
			display.print("End(light)     ");
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 33:
			display.setCursor(0, 0);
			display.print("End(light)     ");
			light_end[1]++;
			if (light_end[1] == 60)
			{
				light_end[1] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 34:
			display.setCursor(0, 0);
			display.print("End(light)     ");
			light_end[1]--;
			if (light_end[1] == -1)
			{
				light_end[1] = 59;
			}
			display.setCursor(0, 1);
			display.print(format_time(light_end));
			break;

		case 35:
			display.setCursor(0, 0);
			display.print("Time(Water)     ");
			water_time[0]++;
			if (water_time[0] == 24)
			{
				water_time[0] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 36:
			display.setCursor(0, 0);
			display.print("Time(Water)     ");
			water_time[0]--;
			if (water_time[0] == -1)
			{
				water_time[0] = 23;
			}
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 37:
			//blink change
			display.setCursor(0, 0);
			display.print("Time(water)     ");
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 38:
			display.setCursor(0, 0);
			display.print("Time(Water)     ");
			water_time[1]++;
			if (water_time[1] == 60)
			{
				water_time[1] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 39:
			display.setCursor(0, 0);
			display.print("Time(Water)     ");
			water_time[1]--;
			if (water_time[1] == -1)
			{
				water_time[1] = 59;
			}
			display.setCursor(0, 1);
			display.print(format_time(water_time));
			break;

		case 40:
			display.setCursor(0, 0);
			display.print("Start(oxygen)     ");
			oxygen_start[0]++;
			if (oxygen_start[0] == 24)
			{
				oxygen_start[0] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 41:
			display.setCursor(0, 0);
			display.print("Start(oxygen)     ");
			oxygen_start[0]--;
			if (oxygen_start[0] == -1)
			{
				oxygen_start[0] = 23;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 42:
			//blink change
			display.setCursor(0, 0);
			display.print("Start(oxygen)     ");
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 43:
			display.setCursor(0, 0);
			display.print("Start(oxygen)     ");
			oxygen_start[1]++;
			if (oxygen_start[1] == 60)
			{
				oxygen_start[1] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 44:
			display.setCursor(0, 0);
			display.print("Start(oxygen)     ");
			oxygen_start[1]--;
			if (oxygen_start[1] == -1)
			{
				oxygen_start[1] = 59;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_start));
			break;

		case 45:
			display.setCursor(0, 0);
			display.print("End(oxygen)     ");
			oxygen_end[0]++;
			if (oxygen_end[0] == 24)
			{
				oxygen_end[0] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 46:
			display.setCursor(0, 0);
			display.print("End(oxygen)     ");
			oxygen_end[0]--;
			if (oxygen_end[0] == -1)
			{
				oxygen_end[0] = 23;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 47:
			//blink change
			display.setCursor(0, 0);
			display.print("End(oxygen)     ");
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 48:
			display.setCursor(0, 0);
			display.print("End(oxygen)     ");
			oxygen_end[1]++;
			if (oxygen_end[1] == 60)
			{
				oxygen_end[1] = 0;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 49:
			display.setCursor(0, 0);
			display.print("End(oxygen)     ");
			oxygen_end[1]--;
			if (oxygen_end[1] == -1)
			{
				oxygen_end[1] = 59;
			}
			display.setCursor(0, 1);
			display.print(format_time(oxygen_end));
			break;

		case 50:
			display.setCursor(0, 0);
			display.print("Temperature    ");
			heat_temperature++;
			if (heat_temperature == 40)
			{
				heat_temperature = 10;
			}
			display.setCursor(0, 1);
			display.print(heat_temperature);
			break;

		case 51:
			display.setCursor(0, 0);
			display.print("Temperature    ");
			heat_temperature--;
			if (heat_temperature == 9)
			{
				heat_temperature = 39;
			}
			display.setCursor(0, 1);
			display.print(heat_temperature);
			break;

		default:
			display.clear();
			display.print("Undefined state!");
		}
		oldstate = state;
	}
}