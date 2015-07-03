
#include <LiquidCrystal.h>
#include "LCD1602_control.h"

// Set the dispaly module
LiquidCrystal myGLCD(8, 9, 4, 5, 6, 7);
char *__LCD_0 = "0";
unsigned char __LCD_min = 0;
unsigned char __LCD_hour = 0;

namespace lcd {
void LCD_setup() {
  myGLCD.clear();
  myGLCD.begin(16, 2);
}

void LCD_work_mode_auto() {
}

void LCD_work_mode_manual() {
}

void LCD_number_mode_time() {
}

void LCD_number_mode_setting() {
}

void LCD_control_mode_local() {
}

void LCD_control_mode_remote() {
}

void LCD_change_ph(char ph) {
  myGLCD.setCursor(LCD_PH_X, LCD_PH_Y);
  if (ph >= 0) {
    myGLCD.print(" ");
  } else {
    myGLCD.print("-");
    ph = -ph;
  }
  __LCD_0[0] = '0' + (int)(ph / 10);
  myGLCD.setCursor(LCD_PH_X + LCD_FONT_WIDTH, LCD_PH_Y);
  myGLCD.print(__LCD_0);
  __LCD_0[0] = '0' + (int)(ph % 10);
  myGLCD.setCursor(LCD_PH_X + LCD_FONT_WIDTH * 2, LCD_PH_Y);
  myGLCD.print(__LCD_0);
  myGLCD.setCursor(LCD_PH_X + LCD_FONT_WIDTH * 3, LCD_PH_Y);
  myGLCD.print("pH");
}

void LCD_change_tem(unsigned char tem) {
  __LCD_0[0] = '0' + (int)(tem / 10);
  myGLCD.setCursor(LCD_TEM_X, LCD_TEM_Y);
  myGLCD.print(__LCD_0);
  __LCD_0[0] = '0' + (int)(tem % 10);
  myGLCD.setCursor(LCD_TEM_X + LCD_FONT_WIDTH, LCD_TEM_Y);
  myGLCD.print(__LCD_0);
  myGLCD.setCursor(LCD_TEM_X + LCD_FONT_WIDTH * 2, LCD_TEM_Y);
  myGLCD.print("`C");
}

void LCD_show_colon() {
  myGLCD.setCursor(LCD_COLON_X, LCD_COLON_1_Y);
  myGLCD.print(":");
}

void LCD_hide_colon() {
  myGLCD.setCursor(LCD_COLON_X, LCD_COLON_1_Y);
  myGLCD.print(" ");
}

void LCD_change_min(unsigned char min) {
  __LCD_min = min;
  __LCD_0[0] = '0' + (int)(min / 10);
  myGLCD.setCursor(LCD_NUMBER_MIN_X, LCD_NUMBER_MIN_Y);
  myGLCD.print(__LCD_0);
  __LCD_0[0] = '0' + (int)(min % 10);
  myGLCD.setCursor(LCD_NUMBER_MIN_X + LCD_NUMBER_WIDTH, LCD_NUMBER_MIN_Y);
  myGLCD.print(__LCD_0);
}

void LCD_change_hour(unsigned char hour) {
  __LCD_hour = hour;
  __LCD_0[0] = '0' + (int)(hour / 10);
  myGLCD.setCursor(LCD_NUMBER_HOUR_X, LCD_NUMBER_HOUR_Y);
  myGLCD.print(__LCD_0);
  __LCD_0[0] = '0' + (int)(hour % 10);
  myGLCD.setCursor(LCD_NUMBER_HOUR_X + LCD_NUMBER_WIDTH, LCD_NUMBER_HOUR_Y);
  myGLCD.print(__LCD_0);
}

void LCD_show_min() {
  int min = __LCD_min;
  LCD_change_min(min);
}

void LCD_hide_min() {
  int min = __LCD_min;
  myGLCD.setCursor(LCD_NUMBER_MIN_X, LCD_NUMBER_MIN_Y);
  myGLCD.print("  ");
}

void LCD_show_hour() {
  int hour = __LCD_hour;
  LCD_change_hour(hour);
}

void LCD_hide_hour() {
  int hour = __LCD_hour;
  myGLCD.setCursor(LCD_NUMBER_HOUR_X, LCD_NUMBER_HOUR_X);
  myGLCD.print("  ");
}

void LCD_change_state(char* str) {
  myGLCD.setCursor(LCD_STATE_X, LCD_STATE_Y);
  myGLCD.print(str);
}

}
