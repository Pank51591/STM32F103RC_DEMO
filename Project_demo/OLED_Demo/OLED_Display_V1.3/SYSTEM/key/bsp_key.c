/*Key1\Key2�����������İ���*/

#include "config.h"

#define USE_UART_SETTIME
#define KEY_DOWN_ACTION       //Ϊ1�������·�Ӧ��Ϊ0����̧��Ӧ 

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //��������
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
	
	/*��������ͬʱ����*/
	if (Key1_Read == 0 && Key2_Read == 0 && Key1_2Down_Flag == 0)       //���һ����־����������������ֹһֱ��Ӧ
	{
		Set_Key1_2Down_Flag;
		gcKeyValue = Keycom1;
	}
		
}
#endif

/*����ɨ�裨���Էŵ���ʱ���ж��*/
uint8_t Key_Check(void)
{
	switch(gcKeyState)
	{
		case 0:
		{
			if(Key1_Read == 0 | Key2_Read == 0)//�а�������ʱ
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
		case 1: //��ȡ������ֵ
		{
			gcKeyCount = 0;
			
			if((Key1_Read == 0)&&(Key2_Read == 1))
			{
				gcKeyValue = Key1;
				Set_KeyReturn_Flag
			}			
			else if((Key2_Read == 0)&&(Key1_Read == 1))  //KEY1����ʱ
			{
				  giKey2Count = 0;  //�����ļ���Ҫ��һ��0
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
		case 2://�������������ɿ�
		{
			if(Key1_Read == 1 && Key2_Read == 1) //û�а�������
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
			else   //��������
			{
				if((Key2_Read == 0)&&(Key1_Read == 1))   //KEY1����3s
				{
					giKey2Count++;
					if(giKey2Count > 300)
					{
						Clr_Key2Down_Flag;   //������Чʱ�����̰��ı�־�����
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

/*��������*/
void Key_Process(void)
{
		switch(Key_Check())
		{
			case Key1:
			{
				printf("KEY0����\r\n");
			}
			break;
			case Key2:
			{
				printf("KEY1����\r\n");
			}
			break;
			case Keycom1:
			{
				printf("��ϰ�������\r\n");
			}
			break;
			case Key1_3s:
			{
			
			}
			break;
			case Key2_3s:
			{
				printf("KEY1����3S\r\n");
			}
			break;		
		}
		 gcKeyValue = 0;
}



