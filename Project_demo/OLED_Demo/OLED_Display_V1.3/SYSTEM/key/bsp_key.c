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
uint8_t gcKeyCount2;

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
uint8_t Key_Check(void)
{
	switch(gcKeyState)
	{
		case 0:
		{
			if(Key1_Read == 0 | Key2_Read == 0)//有按键按下时
			{
					gcKeyCount++;
					if(gcKeyCount >= 5)
					{
						gcKeyCount = 0;
						gcKeyState = 1;
					}
					
			}
			else
			{
				gcKeyCount = 0;
			}	
			
		}
		break;
		case 1: //获取按键的值
		{
			gcKeyCount = 0;
			
			if((Key1_Read == 0)&&(Key2_Read == 1))
			{
				gcKeyValue = Key1;
				Set_KeyReturn_Flag
			}			
			else if((Key2_Read == 0)&&(Key1_Read == 1))  //KEY1按下时
			{
				  giKey2Count = 0;  //长按的计数要清一次0
					Set_Key2Down_Flag;							
          //gcKeyValue = Key2;			
          //Set_KeyReturn_Flag
			}
			else if((Key2_Read == 0)&&(Key1_Read == 0))
			{
				gcKeyValue = Keycom1;
				Set_KeyReturn_Flag
			}
			gcKeyState = 2;
			
		}
		break;
		case 2://按键长按或者松开
		{
			if(Key1_Read == 1 && Key2_Read == 1) //没有按键按下
			{
				gcKeyCount++;
				if(gcKeyCount > 5)
				{
					gcKeyCount = 0;
					if(Key2Down_Flag)
					{
						Clr_Key2Down_Flag;
						gcKeyValue = Key2;
						Set_KeyReturn_Flag;
					}

					gcKeyState = 0;
				}
				
			}
			else   //按键长按
			{
				if((Key2_Read == 0)&&(Key1_Read == 1))   //KEY1长按3s
				{
					giKey2Count++;
					if(giKey2Count > 300)
					{
						Clr_Key2Down_Flag;   //长按生效时，将短按的标志清掉！
						giKey2Count =0;
						gcKeyValue = Key2_3s;
						Set_KeyReturn_Flag;
					}
					
				}
				
			}
			
			
		}
		break;
	}
	
	if(KeyReturn_Flag)
	{
		Clr_KeyReturn_Flag;
		return gcKeyValue;
	}
	else
	{
		return 0;
	}
	
}

/*按键处理*/
void Key_Process(void)
{
		switch(Key_Check())
		{
			case Key1:
			{
				printf("KEY0按下\r\n");
			}
			break;
			case Key2:
			{
				printf("KEY1按下\r\n");
			}
			break;
			case Keycom1:
			{
				printf("组合按键按下\r\n");
			}
			break;
			case Key1_3s:
			{
			
			}
			break;
			case Key2_3s:
			{
				printf("KEY1长按3S\r\n");
			}
			break;		
		}
		 gcKeyValue = 0;
}



