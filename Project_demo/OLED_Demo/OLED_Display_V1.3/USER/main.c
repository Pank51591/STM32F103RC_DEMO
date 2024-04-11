//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : 
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.96寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PB13（SCL）
//              SDA   接PB15（SDA） 
//              RES   接PB11 如果是用4针iic接口这个脚可以不接
//              ----------------------------------------------------------------
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#include "bmp.h"
#include "config.h"
#include "stdio.h"

struct Flag_Class MyFlag;

uint32_t gi1msCount;
uint8_t gc10mscount;
uint8_t gc1sCount;

DHT11_Data_TypeDef DHT11_Data;

char cStr [ 100 ] = { 0 };

 int main(void)
 {	
		u8 t;
	 
	  /*系统滴答定时器初始化*/
    SysTick_Init();	 
		delay_init();	    	   //延时函数初始化	  
		NVIC_Configuration();  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	
    LED_Init();			     //LED端口初始化
	  Key_Init();
    BASIC_TIM_Init();
	  uart_init(115200);
	  DHT11_Init();
		OLED_Init();			 //初始化OLED  
		OLED_Clear(); 
	
		t=' ';  //t是一个字符
		OLED_Clear();
		
	while(1) 
	{		
		if(gc10mscount >= 10)
		{
			gc10mscount = 0;
			Key_Process();
			
//			if (DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS )         //读取 DHT11 温湿度信息
//				{
////					sprintf( cStr, "\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n", 
////									DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
//					printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
//				}
//		    else
//				{					
////					sprintf( cStr, "Read DHT11 ERROR!\r\n" );
//					printf("Read DHT11 ERROR!\r\n");
//				}
			gc1sCount++;
			if(gc1sCount >= 100)  //1s更新一次
			{
				gc1sCount = 0;
				
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
				
				LED1_TOGGLE;
				LED2_TOGGLE;
				
				if (DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS )         //读取 DHT11 温湿度信息
				{
//					sprintf( cStr, "\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n", 
//									DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
					printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
				}
		    else
				{					
//					sprintf( cStr, "Read DHT11 ERROR!\r\n" );
					printf("Read DHT11 ERROR!\r\n");
				}
				
			}
		}
		 	
		
		#if 0    //显示图片
			delay_ms(8000);
			delay_ms(8000);
			OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
			delay_ms(8000);
			delay_ms(8000);
			delay_ms(8000);
			delay_ms(8000);
		#endif
		
	}	  
	
}

