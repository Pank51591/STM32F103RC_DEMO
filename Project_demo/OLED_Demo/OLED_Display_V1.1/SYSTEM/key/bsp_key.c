/*Key1\Key2是两个独立的按键*/

#include "config.h"

#define USE_UART_SETTIME
#define KEY_DOWN_ACTION       //为1按键按下反应，为0按键抬起反应 

//struct rtc_time set_time = {0,27,17,8,11,2022,2};

uint8_t gcKeyState = 0;
uint8_t gcKeyCount = 0;
uint8_t gcKeyValue = 0;
uint16_t giKey1Count = 0;
uint16_t giKey2Count = 0;
uint16_t giKey1_2Count = 0;
uint8_t Disp_hour, Disp_minute;
uint8_t Key1_3sCount = 0;
uint8_t gcKeyLock1,gcKeyLock2,gcKeyLock1_2,gcKeyLock1_3s,gcKeyLock2_3s;


void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //浮空输入
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
}

#if 0
void Get_Key_Value(void)
{
	if(Key1_Read == 0 && Key1Down_Flag == 0)
	{
		Set_Key1Down_Flag;
		#ifdef KEY_DOWN_ACTION
			gcKeyValue = Key1;
		#endif
	}
	
	if (Key2_Read == 0  && Key2Down_Flag == 0)
	{
		Set_Key2Down_Flag;
		#ifdef KEY_DOWN_ACTION
			gcKeyValue = Key2;
		#endif
	}
	
	/*两个按键同时按下*/
	if (Key1_Read == 0 && Key2_Read == 0 && Key1_2Down_Flag == 0)       //最后一个标志用来设置自锁，防止一直反应
	{
		Set_Key1_2Down_Flag;
		gcKeyValue = Keycom1;
	}
		
}
#endif

/*按键扫描（可以放到定时器中断里）*/
void Key_Check(void)
{
	if(Key1_Read == 1)    //按键1没有按下
	{
		gcKeyLock1 = 0;    //按键自锁标志清0
		giKey1Count = 0;
		if(Key1Down_Flag)
		{
			Clr_Key1Down_Flag;
			gcKeyValue = Key1;
			Set_KeyReturn_Flag;
		}
	}
	else if(gcKeyLock1 == 0)     //用else if隐含的是 Key1_Read = 0
	{
		giKey1Count++;
		if(giKey1Count > 20)
		{
			Set_Key1Down_Flag;      //激活短按有效的标志
		}
		if(giKey1Count > 3000)
		{
			Clr_Key1Down_Flag;      //清除短按有效的标志
			giKey1Count = 0;
			gcKeyLock1 = 1;    //按键自锁，避免一直触发
			gcKeyValue = Key1_3s;
			Set_KeyReturn_Flag;
		}
	}
	
	if(Key2_Read == 1)    //按键2没有按下
	{
		gcKeyLock2 = 0;    //按键自锁标志清0
		giKey2Count = 0;
		if(Key2Down_Flag)
		{
			Clr_Key2Down_Flag;
			gcKeyValue = Key2;
			Set_KeyReturn_Flag;
		}
	}
	else if(gcKeyLock2 == 0)     //用else if隐含的是 Key1_Read = 0
	{
		giKey2Count++;
		if(giKey2Count > 20)
		{
			Set_Key2Down_Flag;      //激活短按有效的标志
		}
		if(giKey2Count > 3000)
		{
			Clr_Key2Down_Flag;      //清除短按有效的标志
			giKey2Count = 0;
			gcKeyLock2 = 1;  //按键自锁，避免一直触发
			gcKeyValue = Key2_3s;
			Set_KeyReturn_Flag;
		}
	}
	
	/*独立按键的组合按键*/
	if(Key1_Read == 1 || Key2_Read == 1)    //两个按键不同时按下
	{
		gcKeyLock1_2 = 0;  //按键自锁清零
		giKey1_2Count = 0;
    if(Key1_2Down_Flag)
		{
			gcKeyValue = Keycom1;
			Clr_Key1_2Down_Flag;
		}			
	}
	else if (gcKeyLock1_2 == 0)
	{
		giKey1_2Count++;
		if(giKey1_2Count > 20)
		{
			Set_Key1_2Down_Flag;
//			gcKeyValue = Keycom1;
		}
	}
	
//	if(KeyReturn_Flag)
//	{
//		Clr_KeyReturn_flag;
//		return gcKeyValue;
//	}
//	else
//		return 0;
	
}

void Key_Process(void)
{
	switch(gcKeyValue)
	{
		case Key1 :
		{	
			Set_KeyBuzzer_Flag;
			printf("KEY0被按下\r\n");
//      LED1_TOGGLE;
			
      if(Key1_3sCount != DISPLAY_TIME)
      {				
				//加
				if(Key1_3sCount == SET_HOUR)
				{
					 if(Disp_hour < 24)					
							Disp_hour++;
						else
							Disp_hour = 0;
						
//						set_time.tm_hour = Disp_hour;
				}
				if(Key1_3sCount == SET_MINUTE)
				{
					if(Disp_minute < 60)
						Disp_minute++;
					else
						Disp_minute = 0;
					
//					set_time.tm_min = Disp_minute;
				}
				
//				Time_Adjust(&set_time);
//				//向备份寄存器写入标志
//				BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
				
			}
				gcKeyValue = 0;         //键值清0避免一直触发		

		}
		break;
		case Key2 :
		{
//			/*关闭蜂鸣器*/
//			Clr_Buzzer;
//			TimeAlarm = 0;
//			LED2_TOGGLE;
			Set_KeyBuzzer_Flag;
			printf("KEY1被按下\r\n");
			
			#if 0
			if(Key1_3sCount != DISPLAY_TIME)
			{
        //减			
				if(Key1_3sCount == SET_HOUR)
				{
					if(Disp_hour > 0)
						Disp_hour--;				
					else
						Disp_hour = 23;
					
					set_time.tm_hour = Disp_hour;
				}
				
				if(Key1_3sCount == SET_MINUTE)
				{
					if(Disp_minute > 0)
						Disp_minute--;
					else
						Disp_minute = 59;
					
					set_time.tm_min = Disp_minute;
				}
				
				Time_Adjust(&set_time);
				//向备份寄存器写入标志
				BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);	
				
				gcKeyValue = 0;         //键值清0避免一直触发				
		}
		#endif
		gcKeyValue = 0;
	}
		break;
		/*组合按键*/
		case Keycom1 :
		{
			
			printf("组合按键被按下\r\n");
		
			#ifndef USE_UART_SETTIME 
	
				if(DISPLAY_ON_Flag)
				{
					Clr_DISPLAY_ON_Flag;			
				}
				else
				{
					Set_DISPLAY_ON_Flag;				
				}			
			gcKeyValue = 0;         //键值清0避免一直触发
			#endif
		}
		break;
		/*长按按键1设置时间*/
		case Key1_3s :
		{		
//			LED3_TOGGLE;
			Key1_3sCount++;
			if(Key1_3sCount > 3)
			{
				Key1_3sCount = DISPLAY_TIME;       //显示时间				
			}		
			gcKeyValue = 0;         //键值清0避免一直触发	  
		}
		break;
		case Key2_3s :
		{		
//			 /*使用串口接收设置的时间，输入数字时注意末尾要加回车*/
//			 Time_Regulate_Get(&set_time);
//				
//			 /*用接收到的时间设置RTC*/
//			 Time_Adjust(&set_time);
//			 
//			 //向备份寄存器写入标志
//			 BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
//			
			gcKeyValue = 0;         //键值清0避免一直触发
		}
		break;
		default:
			break;
	}
}



