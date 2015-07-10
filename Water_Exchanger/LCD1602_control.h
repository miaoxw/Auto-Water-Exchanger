/*
  Interface for the main progress to call
  */

namespace lcd
{
	//使用屏幕显示前，调用此方法初始化
	void LCD_setup();

	//change the woter exchanger work mode showing on LCD to "auto"
	//当机器设置为自动换水状态时，调用此方法使屏幕上的工作状态显示为 "auto"
	void LCD_work_mode_auto();
	//change the woter exchanger work mode showing on LCD to "manual"
	//当机器设置为手动换水状态时，调用此方法使屏幕上的工作状态显示为 "manual"
	void LCD_work_mode_manual();

	//当屏幕显示时间为当前时间时，调用此方法使屏幕上的时间模式显示为 "time"
	void LCD_number_mode_time();
	//当屏幕显示时间为设定时间时，调用此方法使屏幕上的时间模式显示为 "setting"
	void LCD_number_mode_setting();

	//当机器由本身控制器操作时，调用此方法使屏幕上的控制模式显示为 "local"
	void LCD_control_mode_local();
	//当机器由远程安卓端操作时，调用此方法使屏幕上的控制模式显示为 "remote"
	void LCD_control_mode_remote();

	//修改屏幕上显示的PH值，变量ph为两位或一位正数负数
	void LCD_change_ph(char ph);

	//修改屏幕上显示的温度值, 变量tem为两位非负数
	void LCD_change_tem(unsigned char tem);

	//显示或隐藏屏幕上的时间区域的冒号
	//可通过反复调用这两个方法实现闪烁效果
	void LCD_show_colon();
	void LCD_hide_colon();

	//修改屏幕上显示的分钟数
	void LCD_change_min(unsigned char min);
	//修改屏幕上显示的小时数
	void LCD_change_hour(unsigned char hour);

	//显示或隐藏屏幕上的时间区域的分钟部分
	//可通过反复调用这两个方法实现闪烁效果
	void LCD_show_min();
	void LCD_hide_min();

	//显示或隐藏屏幕上的时间区域的小时部分
	//可通过反复调用这两个方法实现闪烁效果
	void LCD_show_hour();
	void LCD_hide_hour();

	//屏幕上显示系统状态，任意小于21个字符的英文字符串
	void LCD_change_state(char* str);
}

/*
  Locations of elements on lcd screen
  */

#define LCD_USING_WIDTH 16
#define LCD_USING_HEIGHT 2
#define LCD_WORK_MODE_X 0
#define LCD_WORK_MODE_Y 1
#define LCD_NUMBER_MODE_X 0
#define LCD_NUMBER_MODE_Y 1
#define LCD_NUMBER_HOUR_X 0
#define LCD_NUMBER_HOUR_Y 0
#define LCD_COLON_X 2
#define LCD_COLON_1_Y 0
#define LCD_COLON_2_Y 0
#define LCD_NUMBER_MIN_X 3
#define LCD_NUMBER_MIN_Y 0
#define LCD_CONTROL_MODE_X 0
#define LCD_CONTROL_MODE_Y 1
#define LCD_PH_X 6
#define LCD_PH_Y 0
#define LCD_TEM_X 12
#define LCD_TEM_Y 0
#define LCD_STATE_X 0
#define LCD_STATE_Y 1
#define LCD_LINE_X1 0
#define LCD_LINE_X2 0
#define LCD_LINE_Y 0
#define LCD_FONT_WIDTH 1
#define LCD_NUMBER_WIDTH 1

/*
  Color use of the LCD
  */

#define FONT_COLOR_R 255
#define FONT_COLOR_G 255
#define FONT_COLOR_B 255
#define BACKGROUND_COLOR_R 0
#define BACKGROUND_COLOR_G 0
#define BACKGROUND_COLOR_B 0
