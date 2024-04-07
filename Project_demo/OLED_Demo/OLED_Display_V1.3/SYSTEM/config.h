/*在这里面装所有的头文件*/

#ifndef MYFLAG_H_
#define MYFLAG_H_

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bsp_timer.h"
#include "usart.h"
#include "bsp_key.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_dht11.h"
#include "delay.h"


struct Flag_Class
{
	uint8_t Key1Down;
	uint8_t Key2Down;
	uint8_t Key1_2Down;
	uint8_t KeyReturn;
  uint8_t SetTime;
	uint8_t KeySetTime; 
	uint8_t DISPLAY_ON;
  uint8_t Count500ms;
	uint8_t Count1s;
	uint8_t KeyBuzzer;
	uint8_t Key3s_Buzzer;
	uint8_t AlarmBuzzer;
};

extern  struct Flag_Class MyFlag;     //

#define Key1Down_Flag       MyFlag.Key1Down
#define Set_Key1Down_Flag   MyFlag.Key1Down = 1;
#define Clr_Key1Down_Flag   MyFlag.Key1Down = 0;

#define Key2Down_Flag       MyFlag.Key2Down
#define Set_Key2Down_Flag   MyFlag.Key2Down = 1;
#define Clr_Key2Down_Flag   MyFlag.Key2Down = 0;

#define Key1_2Down_Flag       MyFlag.Key1_2Down
#define Set_Key1_2Down_Flag   MyFlag.Key1_2Down = 1;
#define Clr_Key1_2Down_Flag   MyFlag.Key1_2Down = 0;

#define KeyReturn_Flag          MyFlag.KeyReturn
#define Set_KeyReturn_Flag      MyFlag.KeyReturn = 1;
#define Clr_KeyReturn_Flag      MyFlag.KeyReturn = 0;

#define SetTime_Flag            MyFlag.SetTime
#define Set_SetTime_Flag        MyFlag.SetTime = 1;
#define Clr_SetTime_Flag        MyFlag.SetTime = 0;

#define KeySetTime_Flag       MyFlag.KeySetTime
#define Set_KeySetTime_Flag   MyFlag.KeySetTime = 1;
#define Clr_KeySetTime_Flag   MyFlag.KeySetTime = 0;

#define DISPLAY_ON_Flag        MyFlag.DISPLAY_ON  
#define Set_DISPLAY_ON_Flag    MyFlag.DISPLAY_ON = 1;
#define Clr_DISPLAY_ON_Flag    MyFlag.DISPLAY_ON = 0;

#define Count500ms_Flag        MyFlag.Count500ms
#define Set_Count500ms_Flag    MyFlag.Count500ms = 1;
#define Clr_Count500ms_Flag    MyFlag.Count500ms = 0;

#define Count1s_Flag        MyFlag.Count1s
#define Set_Count1s_Flag    MyFlag.Count1s = 1;
#define Clr_Count1s_Flag    MyFlag.Count1s = 0;

#define KeyBuzzer_Flag        MyFlag.KeyBuzzer
#define Set_KeyBuzzer_Flag    MyFlag.KeyBuzzer = 1;
#define Clr_KeyBuzzer_Flag    MyFlag.KeyBuzzer = 0;

#define Key3s_Buzzer_Flag         MyFlag.Key3s_Buzzer
#define Set_Key3s_Buzzer_Flag     MyFlag.Key3s_Buzzer = 1;
#define Clr_Key3s_Buzzer_Flag     MyFlag.Key3s_Buzzer = 0;

#define AlarmBuzzer_Flag        MyFlag.AlarmBuzzer
#define Set_AlarmBuzzer_Flag    MyFlag.AlarmBuzzer = 1;
#define Clr_AlarmBuzzer_Flag    MyFlag.AlarmBuzzer = 0;


#endif

