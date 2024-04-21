//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : 
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.96��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PB13��SCL��
//              SDA   ��PB15��SDA�� 
//              RES   ��PB11 �������4��iic�ӿ�����ſ��Բ���
//              ----------------------------------------------------------------
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


#include "config.h"
#include "stdio.h"

struct Flag_Class MyFlag;

uint32_t gi1msCount;
uint8_t gc10mscount;
uint8_t gc1sCount;
uint8_t gcPage;
uint8_t t;
extern uint8_t Remote;

float humi,temp;

DHT11_Data_TypeDef DHT11_Data;

char cStr [ 100 ] = { 0 };
char Humi[10];
char Temp[10];

 int main(void)
 {
	  /*ϵͳ�δ�ʱ����ʼ��*/
    SysTick_Init();	 
		delay_init();	    	   //��ʱ������ʼ��	  
		NVIC_Configuration();  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	
	  GENERAL_TIM_Init();
    LED_Init();			     //LED�˿ڳ�ʼ��
	  Key_Init();
    BASIC_TIM_Init();
	  uart_init(115200);
	  DHT11_Init();
		OLED_Init();			 //��ʼ��OLED  
		OLED_Clear(); 
	
		t=' ';  //t��һ���ַ�
		
	while(1) 
	{		
		
		if( Remote != 0 )              //�������������ֵ������յ�ң�ذ����ˣ������ң�ذ���ֵΪ0����Ҫ��Remote�ĳ�ʼֵ��������ж���  
		{
				Remote_Scan(Remote);     //ң�ذ�������
			  Remote = 0;
		} 
		
		if(gc10mscount >= 10)
		{
			gc10mscount = 0;
			Key_Process();

			gc1sCount++;
			if(gc1sCount >= 100)  //1s����һ��
			{
				gc1sCount = 0;
				
				Display_Update();
							
				LED1_TOGGLE;
				LED2_TOGGLE;
				
				if (DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS )         //��ȡ DHT11 ��ʪ����Ϣ
				{
					humi = (float)(DHT11_Data .humi_int + DHT11_Data .humi_deci * 0.1);
					snprintf(Humi,6,"%.2f",humi);
					temp = (float)(DHT11_Data .temp_int + DHT11_Data .temp_deci *0.1);
					snprintf(Temp,6,"%.2f",temp);
//					sprintf( cStr, "\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n", 
//									DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
					//printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
				}
		    else
				{					
//					sprintf( cStr, "Read DHT11 ERROR!\r\n" );
					printf("Read DHT11 ERROR!\r\n");
				}
				
			}
		}
		 	
		
		#if 0    //��ʾͼƬ
			delay_ms(8000);
			delay_ms(8000);
			OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
			delay_ms(8000);
			delay_ms(8000);
			delay_ms(8000);
			delay_ms(8000);
		#endif
		
	}	  
	
}

