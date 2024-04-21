#include "Display.h"
#include "oled.h"
#include "bmp.h"
#include "stdio.h"

extern uint8_t gcPage;
extern uint8_t t;

extern float humi,temp;
extern char Humi[10];
extern char Temp[10];


void Display_Update (void)
{
	switch(gcPage)
	{
		case PAGE0:
		{
			Disp_Page1();
		}
		break;
		case PAGE1:
		{
			Disp_Page2();
		}
		break;
		case PAGE2:
		{
			Disp_Page3();
		}
		break;
		case PAGE3:
		{
		
		}
		break;
		case PAGE4:
		{
		
		}
		break;
	}
}


void Disp_Page1(void)
{
	
	OLED_ShowCHinese(0,0,0); //��
	OLED_ShowCHinese(18,0,1);//��
	OLED_ShowCHinese(36,0,2);//��
	OLED_ShowCHinese(54,0,3);//��
	OLED_ShowCHinese(72,0,4);//ר
	OLED_ShowCHinese(90,0,5);//ҵ
	//OLED_ShowCHinese(108,0,6);//��
	
	//OLED_ShowString(6,3,"0.96' OLED TEST",16);
	OLED_ShowString(8,2," pan ke' Test ",16);  
	OLED_ShowString(20,4,"2024/04/04",16);  
	OLED_ShowString(0,6,"ASCII:",16);  
	OLED_ShowString(63,6,"CODE:",16);  
	OLED_ShowChar(48,6,t,16);    //��ʾASCII�ַ�	
	
	t++;    //���ַ���ascll��������
	if(t>'~')t=' ';
	OLED_ShowNum(103,6,t,3,16);    //��ʾASCII�ַ�����ֵ 	
	//printf("ASCII��%c, Code = %d\r\n", t, t);    //ͨ������1���д�ӡ
}

void Disp_Page2(void)
{
	
	OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
}


void Disp_Page3(void)
{
	OLED_ShowString(20,2,"Temp: ",16);  
//	OLED_ShowNum(70,2,temp,3,16);    //��ʾASCII�ַ�����ֵ
	OLED_ShowString2(63,2,Temp,16);
	OLED_ShowChar(108,2,'C',16);
	OLED_ShowString(20,4,"Humi: ",16);
//	OLED_ShowNum(70,4,humi,3,16);
	OLED_ShowString2(63,4,Humi,16);
	OLED_ShowChar(108,4,'%',16);
}

