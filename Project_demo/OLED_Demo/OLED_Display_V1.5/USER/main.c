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
	  /*系统滴答定时器初始化*/
    SysTick_Init();	 
		delay_init();	    	   //延时函数初始化	  
		NVIC_Configuration();  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	
	  GENERAL_TIM_Init();
    LED_Init();			     //LED端口初始化
	  Key_Init();
    BASIC_TIM_Init();
	  uart_init(115200);
	  DHT11_Init();
		OLED_Init();			 //初始化OLED  
		OLED_Clear(); 
	
		t=' ';  //t是一个字符
		
	while(1) 
	{		
		
		if( Remote != 0 )              //如果变量里面有值则代表收到遥控按键了，如果有遥控按键值为0就需要改Remote的初始值和这里的判断了  
		{
				Remote_Scan(Remote);     //遥控按键处理
			  Remote = 0;
		} 
		
		if(gc10mscount >= 10)
		{
			gc10mscount = 0;
			Key_Process();

			gc1sCount++;
			if(gc1sCount >= 100)  //1s更新一次
			{
				gc1sCount = 0;
				
				Display_Update();
							
				LED1_TOGGLE;
				LED2_TOGGLE;
				
				if (DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS )         //读取 DHT11 温湿度信息
				{
					humi = (float)(DHT11_Data .humi_int + DHT11_Data .humi_deci * 0.1);
					snprintf(Humi,6,"%.2f",humi);
					temp = (float)(DHT11_Data .temp_int + DHT11_Data .temp_deci *0.1);
					snprintf(Temp,6,"%.2f",temp);
//					sprintf( cStr, "\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n", 
//									DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
					//printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );
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

