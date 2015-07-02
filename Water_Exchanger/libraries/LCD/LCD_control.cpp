
#include <UTFT.h>
#include "LCD_control.h"

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Set the dispaly module
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);
char *__LCD_0 = "0";
unsigned char __LCD_min = 0;
unsigned char __LCD_hour = 0;

void LCD_setup(){
  randomSeed(analogRead(0));
  //  Setup the LCD
  //  Initializes twice to improve reliability
  myGLCD.InitLCD();
  myGLCD.InitLCD();

  myGLCD.clrScr();
}

void LCD_work_mode_auto(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("AUTO  ", LCD_WORK_MODE_X, LCD_WORK_MODE_Y);
}

void LCD_work_mode_manual(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("MANUAL", LCD_WORK_MODE_X, LCD_WORK_MODE_Y);
}

void LCD_number_mode_time(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("TIME   ", LCD_NUMBER_MODE_X, LCD_NUMBER_MODE_Y);
}

void LCD_number_mode_setting(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("SETTING", LCD_NUMBER_MODE_X, LCD_NUMBER_MODE_Y);
}

void LCD_control_mode_local(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("LOCAL ", LCD_CONTROL_MODE_X, LCD_CONTROL_MODE_Y);
}

void LCD_control_mode_remote(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  myGLCD.print("REMOTE", LCD_CONTROL_MODE_X, LCD_CONTROL_MODE_Y);
}

void LCD_change_ph(char ph){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  if(ph>=0){
    myGLCD.print(" ", LCD_PH_X, LCD_PH_Y);
  }else{
    myGLCD.print("-", LCD_PH_X, LCD_PH_Y);
    ph = -ph;
  }
  __LCD_0[0] = '0'+(int)(ph/10);
  myGLCD.print(__LCD_0, LCD_PH_X+LCD_FONT_WIDTH, LCD_PH_Y);
  __LCD_0[0] = '0'+(int)(ph%10);
  myGLCD.print(__LCD_0, LCD_PH_X+LCD_FONT_WIDTH*2, LCD_PH_Y);
  myGLCD.print("pH", LCD_PH_X+LCD_FONT_WIDTH*3, LCD_PH_Y);
}

void LCD_change_tem(unsigned char tem){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SmallFont);
  __LCD_0[0] = '0'+(int)(tem/10);
  myGLCD.print(__LCD_0, LCD_TEM_X, LCD_TEM_Y);
  __LCD_0[0] = '0'+(int)(tem%10);
  myGLCD.print(__LCD_0, LCD_TEM_X+LCD_FONT_WIDTH, LCD_TEM_Y);
  myGLCD.print("C", LCD_TEM_X+LCD_FONT_WIDTH*2, LCD_TEM_Y);
}

void LCD_show_colon(){
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.fillCircle(LCD_COLON_X, LCD_COLON_1_Y, 5);
  myGLCD.fillCircle(LCD_COLON_X, LCD_COLON_2_Y, 5);
}

void LCD_hide_colon(){
  myGLCD.setColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
  myGLCD.fillCircle(LCD_COLON_X, LCD_COLON_1_Y, 5);
  myGLCD.fillCircle(LCD_COLON_X, LCD_COLON_2_Y, 5);
}

void LCD_change_min(unsigned char min){
  __LCD_min = min;
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(min/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X, LCD_NUMBER_MIN_Y);
  __LCD_0[0] = '0'+(int)(min%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X+LCD_NUMBER_WIDTH, LCD_NUMBER_MIN_Y);
}

void LCD_change_hour(unsigned char hour){
  __LCD_hour = hour;
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(hour/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X, LCD_NUMBER_HOUR_Y);
  __LCD_0[0] = '0'+(int)(hour%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X+LCD_NUMBER_WIDTH, LCD_NUMBER_HOUR_Y);
}

void LCD_show_min(){
  int min = __LCD_min;
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(min/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X, LCD_NUMBER_MIN_Y);
  __LCD_0[0] = '0'+(int)(min%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X+LCD_NUMBER_WIDTH, LCD_NUMBER_MIN_Y);
}

void LCD_hide_min(){
  int min = __LCD_min;
  myGLCD.setColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(min/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X, LCD_NUMBER_MIN_Y);
  __LCD_0[0] = '0'+(int)(min%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_MIN_X+LCD_NUMBER_WIDTH, LCD_NUMBER_MIN_Y);
}

void LCD_show_hour(){
  int hour = __LCD_hour;
  myGLCD.setColor(FONT_COLOR_R, FONT_COLOR_G, FONT_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(hour/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X, LCD_NUMBER_HOUR_Y);
  __LCD_0[0] = '0'+(int)(hour%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X+LCD_NUMBER_WIDTH, LCD_NUMBER_HOUR_Y);
}

void LCD_hide_hour(){
  int hour = __LCD_hour;
  myGLCD.setColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
  myGLCD.setFont(SevenSegNumFont);
  __LCD_0[0] = '0'+(int)(hour/10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X, LCD_NUMBER_HOUR_Y);
  __LCD_0[0] = '0'+(int)(hour%10);
  myGLCD.print(__LCD_0, LCD_NUMBER_HOUR_X+LCD_NUMBER_WIDTH, LCD_NUMBER_HOUR_Y);
}
