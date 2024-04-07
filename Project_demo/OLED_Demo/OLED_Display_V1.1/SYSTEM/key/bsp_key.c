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
void Key_Check(void)
{
	if(Key1_Read == 1)    //����1û�а���
	{
		gcKeyLock1 = 0;    //����������־��0
		giKey1Count = 0;
		if(Key1Down_Flag)
		{
			Clr_Key1Down_Flag;
			gcKeyValue = Key1;
			Set_KeyReturn_Flag;
		}
	}
	else if(gcKeyLock1 == 0)     //��else if�������� Key1_Read = 0
	{
		giKey1Count++;
		if(giKey1Count > 20)
		{
			Set_Key1Down_Flag;      //����̰���Ч�ı�־
		}
		if(giKey1Count > 3000)
		{
			Clr_Key1Down_Flag;      //����̰���Ч�ı�־
			giKey1Count = 0;
			gcKeyLock1 = 1;    //��������������һֱ����
			gcKeyValue = Key1_3s;
			Set_KeyReturn_Flag;
		}
	}
	
	if(Key2_Read == 1)    //����2û�а���
	{
		gcKeyLock2 = 0;    //����������־��0
		giKey2Count = 0;
		if(Key2Down_Flag)
		{
			Clr_Key2Down_Flag;
			gcKeyValue = Key2;
			Set_KeyReturn_Flag;
		}
	}
	else if(gcKeyLock2 == 0)     //��else if�������� Key1_Read = 0
	{
		giKey2Count++;
		if(giKey2Count > 20)
		{
			Set_Key2Down_Flag;      //����̰���Ч�ı�־
		}
		if(giKey2Count > 3000)
		{
			Clr_Key2Down_Flag;      //����̰���Ч�ı�־
			giKey2Count = 0;
			gcKeyLock2 = 1;  //��������������һֱ����
			gcKeyValue = Key2_3s;
			Set_KeyReturn_Flag;
		}
	}
	
	/*������������ϰ���*/
	if(Key1_Read == 1 || Key2_Read == 1)    //����������ͬʱ����
	{
		gcKeyLock1_2 = 0;  //������������
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
			printf("KEY0������\r\n");
//      LED1_TOGGLE;
			
      if(Key1_3sCount != DISPLAY_TIME)
      {				
				//��
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
//				//�򱸷ݼĴ���д���־
//				BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
				
			}
				gcKeyValue = 0;         //��ֵ��0����һֱ����		

		}
		break;
		case Key2 :
		{
//			/*�رշ�����*/
//			Clr_Buzzer;
//			TimeAlarm = 0;
//			LED2_TOGGLE;
			Set_KeyBuzzer_Flag;
			printf("KEY1������\r\n");
			
			#if 0
			if(Key1_3sCount != DISPLAY_TIME)
			{
        //��			
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
				//�򱸷ݼĴ���д���־
				BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);	
				
				gcKeyValue = 0;         //��ֵ��0����һֱ����				
		}
		#endif
		gcKeyValue = 0;
	}
		break;
		/*��ϰ���*/
		case Keycom1 :
		{
			
			printf("��ϰ���������\r\n");
		
			#ifndef USE_UART_SETTIME 
	
				if(DISPLAY_ON_Flag)
				{
					Clr_DISPLAY_ON_Flag;			
				}
				else
				{
					Set_DISPLAY_ON_Flag;				
				}			
			gcKeyValue = 0;         //��ֵ��0����һֱ����
			#endif
		}
		break;
		/*��������1����ʱ��*/
		case Key1_3s :
		{		
//			LED3_TOGGLE;
			Key1_3sCount++;
			if(Key1_3sCount > 3)
			{
				Key1_3sCount = DISPLAY_TIME;       //��ʾʱ��				
			}		
			gcKeyValue = 0;         //��ֵ��0����һֱ����	  
		}
		break;
		case Key2_3s :
		{		
//			 /*ʹ�ô��ڽ������õ�ʱ�䣬��������ʱע��ĩβҪ�ӻس�*/
//			 Time_Regulate_Get(&set_time);
//				
//			 /*�ý��յ���ʱ������RTC*/
//			 Time_Adjust(&set_time);
//			 
//			 //�򱸷ݼĴ���д���־
//			 BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
//			
			gcKeyValue = 0;         //��ֵ��0����һֱ����
		}
		break;
		default:
			break;
	}
}



