//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : 
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.69��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
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

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"

 int main(void)
 {	
		u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	
//		LED_Init();			     //LED�˿ڳ�ʼ��
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear(); 
	
		t=' ';  //t��һ���ַ�
		OLED_Clear();
		
	while(1) 
	{		
		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//��
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//ר
		OLED_ShowCHinese(90,0,5);//ҵ
//		OLED_ShowCHinese(108,0,6);//��
		
//		OLED_ShowString(6,3,"0.96' OLED TEST",16);
		OLED_ShowString(8,2," pan ke' Test ",16);  
	  OLED_ShowString(20,4,"2024/04/04",16);  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	
		
		t++;    //���ַ���ascll��������
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 			
		delay_ms(8000);
		delay_ms(8000);
		
//		delay_ms(8000);
//		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ��ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
//		delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
	}	  
	
}
