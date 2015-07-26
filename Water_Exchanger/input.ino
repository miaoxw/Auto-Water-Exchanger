#include <LiquidCrystal.h>
#include "input.h"
#include "ports.h"
/**
 * Date: 2015-07-16
 * Author: Song Yang
 * Email: ysong12@software.nju.edu.cn
 */

using Ports::LCD_RS;
using Ports::LCD_RW;
using Ports::LCD_EN;
using Ports::LCD_D4;
using Ports::LCD_D5;
using Ports::LCD_D6;
using Ports::LCD_D7;

namespace Input
{
	LiquidCrystal display(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

	//time storage
	int water_time[2] = { 12, 00 };
	int light_start[2] = { 12, 00 };
	int light_end[2] = { 12, 00 };
	int oxygen_start[2] = { 12, 00 };
	int oxygen_end[2] = { 12, 00 };
	int heat_temperature = 28;
};

void Input::init()
{
	display.clear();
	display.begin(16, 2);
	display.setCursor(0, 0);
	display.print("PH=7  25c       ");
	display.setCursor(0, 1);
	display.print("2015-7-15 12:00       ");
}

String Input::format_time(int array[2])
{
	{
		String str = "";
		if (array[0] < 10)
		{
			str = str + "0";
		}
		str = str + array[0];
		str = str + ":";
		if (array[1] < 10)
		{
			str = str + "0";
		}
		str = str + array[1];
		return str;
	}
}

// Convert ADC value to key number
// origin: right0 up1 down2 left3 select4
// select0 left1 up2 down3 right4
unsigned int Input::mapKey(unsigned int input)
{
	unsigned int keyMap[] = { 4, 2, 3, 1, 0 };

	if (input >= 5 || input < 0)
		return -1;		//Invalid input
	return keyMap[input];
}