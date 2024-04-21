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
	
	OLED_ShowCHinese(0,0,0); //电
	OLED_ShowCHinese(18,0,1);//子
	OLED_ShowCHinese(36,0,2);//科
	OLED_ShowCHinese(54,0,3);//技
	OLED_ShowCHinese(72,0,4);//专
	OLED_ShowCHinese(90,0,5);//业
	//OLED_ShowCHinese(108,0,6);//技
	
	//OLED_ShowString(6,3,"0.96' OLED TEST",16);
	OLED_ShowString(8,2," pan ke' Test ",16);  
	OLED_ShowString(20,4,"2024/04/04",16);  
	OLED_ShowString(0,6,"ASCII:",16);  
	OLED_ShowString(63,6,"CODE:",16);  
	OLED_ShowChar(48,6,t,16);    //显示ASCII字符	
	
	t++;    //将字符的ascll码往后移
	if(t>'~')t=' ';
	OLED_ShowNum(103,6,t,3,16);    //显示ASCII字符的码值 	
	//printf("ASCII：%c, Code = %d\r\n", t, t);    //通过串口1进行打印
}

void Disp_Page2(void)
{
	
	OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
}


void Disp_Page3(void)
{
	OLED_ShowString(20,2,"Temp: ",16);  
//	OLED_ShowNum(70,2,temp,3,16);    //显示ASCII字符的码值
	OLED_ShowString2(63,2,Temp,16);
	OLED_ShowChar(108,2,'C',16);
	OLED_ShowString(20,4,"Humi: ",16);
//	OLED_ShowNum(70,4,humi,3,16);
	OLED_ShowString2(63,4,Humi,16);
	OLED_ShowChar(108,4,'%',16);
}

