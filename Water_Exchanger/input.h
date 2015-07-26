#ifndef INPUT_H
#define INPUT_H
#include <LiquidCrystal.h>
#include <WString.h>

namespace Input
{
	extern LiquidCrystal display;

	void operateFSM(unsigned int keyCode);
	unsigned int mapKey(unsigned int input);
	String format_time(int array[]);
	unsigned int mapKey(unsigned int input);

	void init();

	//time storage
	extern int water_time[2];
	extern int light_start[2];
	extern int light_end[2];
	extern int oxygen_start[2];
	extern int oxygen_end[2];
}

#endif