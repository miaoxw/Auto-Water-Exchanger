#include <LiquidCrystal.h>
/**
 * Date: 2015-07-16
 * Author: Song Yang
 * Email: ysong12@software.nju.edu.cn
 */
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

int state_fsm[51][5]={
{2,0,0,0,0},
{5,1,4,3,0},
{6,1,2,4,0},
{7,1,3,2,0},
{10,2,13,8,0},
{19,3,18,16,0},
{15,4,0,0,0},
{9,2,5,11,0},
{9,2,5,11,0},
{10,2,13,8,0},
{12,2,8,13,0},
{12,2,8,13,0},
{14,2,11,5,0},
{14,2,11,5,0},
{15,4,0,0,0},
{21,3,6,17,0},
{22,3,16,18,0},
{24,3,17,6,0},
{20,27,25,26,27},
{6,32,30,31,32},
{16,37,35,36,37},
{23,42,40,41,42},
{17,47,45,46,47},
{18,0,50,51,0},
{20,27,25,26,27},
{20,27,25,26,27},
{20,19,28,29,19},
{20,19,28,29,19},
{20,19,28,29,19},
{6,32,30,31,32},
{6,32,30,31,32},
{6,20,33,34,20},
{6,20,33,34,20},
{6,20,33,34,20},
{16,37,35,36,37},
{16,37,35,36,37},
{16,21,38,39,21},
{16,21,38,39,21},
{16,21,38,39,21},
{23,42,40,41,42},
{23,42,40,41,42},
{23,22,43,44,22},
{23,22,43,44,22},
{23,22,43,44,22},
{17,47,45,46,47},
{17,47,45,46,47},
{17,23,48,49,23},
{17,23,48,49,23},
{17,23,48,49,23},
{18,0,50,51,0},
{18,0,50,51,0},
};
namespace input
{
int adc_key_val[5] = {50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int state = 1;
int oldstate = 1;
//0 means off, 1 means on
int light_state = 0;
int water_state = 0;
int oxygen_state = 0;
int heat_state = 0;
int automate_state = 0;
//time storage
int water_time[2] = {12,00};
int light_start[2] = {12,00};
int light_end[2] = {12,00};
int oxygen_start[2] = {12,00};
int oxygen_end[2] = {12,00};
int heat_temperature = 28;
}

using namespace input;

void setup()
{
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("PH=7  25c       ");
  lcd.setCursor(0, 1);
  lcd.print("2015-7-15 12:00       ");
}

void loop()
{
  if(automate_state == 1)
  {
    //TODO
  }
  
  adc_key_in = analogRead(0);    // read the value from the sensor
  key = get_key(adc_key_in);  // convert into key press
  delay(25);  // wait for debounce time
  adc_key_in = analogRead(0);    // read the value from the sensor
  key = get_key(adc_key_in);    // convert into key press
 
  if(key>=0)
  {
    state = state_fsm[oldstate-1][key];
    if(state !=0 )
    {
      lcd.clear();
      switch(state)
      {
        case 1:
        lcd.setCursor(0, 0);
        lcd.print("PH=7  25c       ");
        lcd.setCursor(0, 1);
        lcd.print("2015-7-15 12:00       ");
        break;
        
        case 2:
        lcd.setCursor(0, 0);
        lcd.print("Mode choice:          ");
        lcd.setCursor(0, 1);
        lcd.print("Immediately    ");
        break;
        
        case 3:
        lcd.setCursor(0, 0);
        lcd.print("Mode choice:          ");
        lcd.setCursor(0, 1);
        lcd.print("Period       ");
        break;
        
        case 4:
        lcd.setCursor(0, 0);
        lcd.print("Mode choice:          ");
        lcd.setCursor(0, 1);
        lcd.print("Automate       ");
        break;
        
        case 5:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        lcd.setCursor(0, 1);
        if(light_state == 0)
        {
           lcd.print("light off      ");
        }else if(light_state == 1)
        {
          lcd.print("light on      ");
        }else
        {
          lcd.print("light err 5     ");
        }
        break;
        
        case 6:
        lcd.setCursor(0, 0);
        lcd.print("Period      ");
        lcd.setCursor(0, 1);    
        lcd.print("Set light      ");      
        break;
        
        case 7:
        lcd.setCursor(0, 0);
        lcd.print("Automate      ");
        lcd.setCursor(0, 1);
        if(automate_state == 0)
        {
          lcd.print("Automate off    "); 
        }else if(automate_state == 1)
        {
          lcd.print("Automate on    "); 
        }else
        {
          lcd.print("Automate err 7    "); 
        }
        break;
        
        case 8:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        lcd.setCursor(0, 1);
        lcd.print("Change Water?          ");
        break;
        
        case 9:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        lcd.setCursor(0, 1);
        lcd.print("Water changing...     ");
        //TODO
        //open water valve
      
        break;
        
        case 10:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        if(light_state == 0)
        {
          //TODO
          //open light
          light_state = 1;
          lcd.setCursor(0, 1);
          lcd.print("Light on     ");
        }else if(light_state == 1)
        {
          //TODO
          //close light
          light_state = 0;
          lcd.setCursor(0, 1);
          lcd.print("Light off     ");
        }else
        {
          lcd.setCursor(0, 1);
          lcd.print("Light err 10   ");
        }
        break;
        
        case 11:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        if(oxygen_state == 0)
        {
          lcd.setCursor(0, 1);
          lcd.print("Oxygen off     ");
        }else if(oxygen_state == 1)
        {
          lcd.setCursor(0, 1);
          lcd.print("Oxygen on     ");
        }else
        {
          lcd.setCursor(0, 1);
          lcd.print("Oxygen err 11    ");
        }     
        break;
        
        case 12:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        if(oxygen_state == 0)
        {
          //TODO
          //open oxygen pump
          oxygen_state = 1;
          lcd.setCursor(0, 1);
          lcd.print("Oxygen on     ");
        }else if(oxygen_state == 1)
        {
          //TODO
          //close oxygen pump
          oxygen_state = 0;
          lcd.setCursor(0, 1);
          lcd.print("Oxygen off     ");
        }else
        {
          lcd.setCursor(0, 1);
          lcd.print("Oxygen err 12     ");
        }
        break;
        
        case 13:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");       
        lcd.setCursor(0, 1);
        if(heat_state == 0)
        {
          lcd.print("heat off     ");
        }else if(heat_state == 1)
        {
          lcd.print("heat on     ");
        }else
        {
          lcd.print("heat err 13     ");
        }                
        break;
        
        case 14:
        lcd.setCursor(0, 0);
        lcd.print("Immediately      ");
        lcd.setCursor(0, 1);
        if(heat_state == 0)
        {
          //TODO
          //open heat siwtch
          heat_state = 1;
          lcd.print("heat on     ");
        }else if(heat_state == 1)
        {
          //TODO
          //close heat siwtch
          heat_state = 0;
          lcd.print("heat off       ");
        }else
        {
          lcd.print("heat err 14     ");
        }       
        break;

        case 15:
        lcd.setCursor(0, 0);
        lcd.print("Automate      ");
        lcd.setCursor(0, 1);
        if(automate_state == 0)
        {
          automate_state = 1;
          lcd.print("Automate on");
        }else if(automate_state == 1)
        {
          automate_state = 0;
          lcd.print("Automate off");
        }else
        {
          lcd.print("Automate err 15  ");
        }
        break;

        case 16:
        lcd.setCursor(0, 0);
        lcd.print("Period      ");
        lcd.setCursor(0, 1);
        lcd.print("Set change water     ");
        break;

        case 17:
        lcd.setCursor(0, 0);
        lcd.print("Period      ");
        lcd.setCursor(0, 1);
        lcd.print("Set oxygen     ");
        break;

        case 18:
        lcd.setCursor(0, 0);
        lcd.print("Period      ");
        lcd.setCursor(0, 1);
        lcd.print("Set heat     ");
        break;

        case 19:
        lcd.setCursor(0, 0);
        lcd.print("Start(light)      ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 20:
        lcd.setCursor(0, 0);
        lcd.print("End(light)      ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 21:
        lcd.setCursor(0, 0);
        lcd.print("Time(water)      ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 22:
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)      ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 23:
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)      ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 24:
        lcd.setCursor(0, 0);
        lcd.print("Temperature     ");
        lcd.setCursor(0, 1);
        lcd.print(heat_temperature);
        break;

        case 25:
        lcd.setCursor(0, 0);
        lcd.print("Start(light)     ");
        light_start[0]++;
        if(light_start[0] == 24)
        {
          light_start[0] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 26:
        lcd.setCursor(0, 0);
        lcd.print("Start(light)     ");
        light_start[0]--;
        if(light_start[0] == -1)
        {
          light_start[0] = 23;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 27:
        //blink
        lcd.setCursor(0, 0);
        lcd.print("Start(light)     ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 28:
        lcd.setCursor(0, 0);
        lcd.print("Start(light)     ");
        light_start[1]++;
        if(light_start[1] == 60)
        {
          light_start[1] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 29:
        lcd.setCursor(0, 0);
        lcd.print("Start(light)     ");
        light_start[1]--;
        if(light_start[1] == -1)
        {
          light_start[1] = 59;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_start));
        break;

        case 30:
        lcd.setCursor(0, 0);
        lcd.print("End(light)     ");
        light_end[0]++;
        if(light_end[0] == 24)
        {
          light_end[0] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 31:
        lcd.setCursor(0, 0);
        lcd.print("End(light)     ");
        light_end[0]--;
        if(light_end[0] == -1)
        {
          light_end[0] = 23;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 32:
        //blink change
        lcd.setCursor(0, 0);
        lcd.print("End(light)     ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 33:
        lcd.setCursor(0, 0);
        lcd.print("End(light)     ");
        light_end[1]++;
        if(light_end[1] == 60)
        {
          light_end[1] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 34:
        lcd.setCursor(0, 0);
        lcd.print("End(light)     ");
        light_end[1]--;
        if(light_end[1] == -1)
        {
          light_end[1] = 59;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(light_end));
        break;

        case 35:
        lcd.setCursor(0, 0);
        lcd.print("Time(Water)     ");
        water_time[0]++;
        if(water_time[0] == 24)
        {
          water_time[0] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 36:
        lcd.setCursor(0, 0);
        lcd.print("Time(Water)     ");
        water_time[0]--;
        if(water_time[0] == -1)
        {
          water_time[0] = 23;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 37:
        //blink change
        lcd.setCursor(0, 0);
        lcd.print("Time(water)     ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 38:
        lcd.setCursor(0, 0);
        lcd.print("Time(Water)     ");
        water_time[1]++;
        if(water_time[1] == 60)
        {
          water_time[1] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 39:
        lcd.setCursor(0, 0);
        lcd.print("Time(Water)     ");
        water_time[1]--;
        if(water_time[1] == -1)
        {
          water_time[1] = 59;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(water_time));
        break;

        case 40:
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)     ");
        oxygen_start[0]++;
        if(oxygen_start[0] == 24)
        {
          oxygen_start[0] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 41:
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)     ");
        oxygen_start[0]--;
        if(oxygen_start[0] == -1)
        {
          oxygen_start[0] = 23;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 42:
        //blink change
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)     ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 43:
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)     ");
        oxygen_start[1]++;
        if(oxygen_start[1] == 60)
        {
          oxygen_start[1] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 44:
        lcd.setCursor(0, 0);
        lcd.print("Start(oxygen)     ");
        oxygen_start[1]--;
        if(oxygen_start[1] == -1)
        {
          oxygen_start[1] = 59;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_start));
        break;

        case 45:
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)     ");
        oxygen_end[0]++;
        if(oxygen_end[0] == 24)
        {
          oxygen_end[0] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 46:
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)     ");
        oxygen_end[0]--;
        if(oxygen_end[0] == -1)
        {
          oxygen_end[0] = 23;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 47:
        //blink change
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)     ");
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 48:
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)     ");
        oxygen_end[1]++;
        if(oxygen_end[1] == 60)
        {
          oxygen_end[1] = 0;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 49:
        lcd.setCursor(0, 0);
        lcd.print("End(oxygen)     ");
        oxygen_end[1]--;
        if(oxygen_end[1] == -1)
        {
          oxygen_end[1] = 59;
        }
        lcd.setCursor(0, 1);
        lcd.print(format_time(oxygen_end));
        break;

        case 50:
        lcd.setCursor(0, 0);
        lcd.print("Temperature    ");
        heat_temperature++;
        if(heat_temperature == 40)
        {
          heat_temperature = 10;
        }
        lcd.setCursor(0, 1);
        lcd.print(heat_temperature);
        break;

        case 51:
        lcd.setCursor(0, 0);
        lcd.print("Temperature    ");
        heat_temperature--;
        if(heat_temperature == 9)
        {
          heat_temperature = 39;
        }
        lcd.setCursor(0, 1);
        lcd.print(heat_temperature);
        break;

        default:
        lcd.clear();
        lcd.print("Undefined state!");
      }
      oldstate=state;
    }
  }
  
  delay(200);
}

String format_time(int array[2])
{
  String str="";
  if(array[0] < 10)
  {
    str = str+"0";
  }
  str = str+array[0];
  str = str+":";
  if(array[1] < 10)
  {
    str = str+"0";
  }
  str = str+array[1];
  return str;
}


// Convert ADC value to key number
// origin: right0 up1 down2 left3 select4
// select0 left1 up2 down3 right4
int get_key(unsigned int input)
{
  int result;
  int k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      result =  k;
      break;
    }
  }

  if (k >= NUM_KEYS)result = -1;  // No valid key pressed
  
  if(result == 0)
  {
    result = 4;
  }else if( result == 1)
  {
    result = 2;
  }else if( result == 2)
  {
    result = 3;
  }else if( result == 3)
  {
    result = 1;
  }else if( result == 4)
  {
    result = 0;
  }
  return result;
}

