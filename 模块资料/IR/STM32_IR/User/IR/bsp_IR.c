#include "bsp_IR.h"
#include "bsp_usart_dma.h"
#include "sys.h"

int Non = 0;     // Non 主要用来调试，可以将它看成是一个标志
int Add_Data = 0;
int Con_Data = 0;

//初始化红外和设置中断
void Infrared_Init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	EXTI_InitTypeDef	EXTI_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_8;
  //GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
	
	EXTI_InitStruct.EXTI_Line	= EXTI_Line8;
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
	EXTI_InitStruct.EXTI_Mode	= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;//上升和下降沿触发中断
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel				= EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd			= ENABLE;
	/*配置中断优先级*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority		= 0;
	NVIC_Init(&NVIC_InitStruct);
	
}

/*********************************************************
***函数名：
***函数功能：通过外部接收中断，来对红外接收到的信号进行解码
***参数：  Non
***返回值：
**********************************************************/
void EXTI9_5_IRQHandler()
{
	int count = 0;
	EXTI_ClearITPendingBit(EXTI_Line8);      //清除EXTI的行挂起位
	
	printf("%d", Non);   //调试代码
	
	Non = 0;
//	if(Add_Data != 0 && Con_Data != 0)
//		return;
	
	if(!ReadGPA8)
		{	
		//引导码9ms低电平
		while(!ReadGPA8)   //
		{
			delay_ms(1);
			if(++count > 12)
			{
				Non = -11;
				return;     //跳出while循环
			}	
		}
		
		if(count < 6)
		{
			Non = -12;
			return;
		}
		count = 0;
		
		//引导码4.5ms高电平
		while(ReadGPA8)
		{
			delay_ms(1);
			if(++count > 8)
			{
				Non = -13;
				return;
			}
		}
			
		if(count < 4)
		{
			Non = -14;
			return;
		}
		count = 0;
		
		//开始接收数据并检验
		GetData();
		
		if(Non != 0)
			return;
		
		//检测结束位
		
		printf("AData:%d  CData:%d\r\n", Add_Data, Con_Data);
		Non = 0;
	}
	else
	{
		Non = -10;
	}
}

/*********************************************************
***函数名：GetData
***函数功能：
***参数：
***返回值：
**********************************************************/
void GetData()
{
	int count = 0;
	int i = 0;
	
	if(!ReadGPA8){
		//接收地址码开始
		Add_Data = 0;
		
		while(i < 8)
		{
			while(!ReadGPA8)    //读到低电平
			{
				delay_us(1);
				if(++count > 600)
				{
					Non = -21;
					return;
				}
			}
//			if(count < 400){
//				Non = -22;
//				return;
//			}			
			
			count = 0;
	
			while(ReadGPA8)   //读到高电平
			{     
				delay_us(1);
				if(++count > 600)
				{
					Add_Data |= (0x1 << (7 - i));     //
				}
			}
			
			if(count > 180)
			{
				Non = -23;
				return;
			}			
			
			count = 0;	
			i++;
		}
		
		//检验地址码（反码）
		i = 0;
		while(i < 8)
		{		
			while(!ReadGPA8)  //读到低电平
			{      
				delay_us(1);
				if(++count > 600)
				{
					Non = -24;
					return;     //跳出while循环
				}
			}
			if(count < 45){
				Non = -25;
				return;
			}
			
			count = 0;

			while(ReadGPA8)//读到高电平
			{       
				delay_us(1);
				if(++count > 600){
					if((Add_Data & (0x1 << (7 - i))) != 0){
						Non = -31;
						return;
					}
				}
			}
			
			/*当校验成功时，正码与反码相与的结果为0*/
			if(count < 600 && ((Add_Data & (0x1 << (7 - i))) == 0))
			{
				Non = -32;
				return;
			}
			if(count > 180)
			{
				Non = -26;
				return;
			}		
			count = 0;
			i++;
		}	
		
		//接收控制码开始
		Con_Data = 0;
		i = 0;
		while(i < 8)
		{
			while(!ReadGPA8)      //读到低电平
			{        
				delay_us(1);
				if(++count > 600)
				{
					Non = -41;
					return;
				}
			}
			if(count < 400){
				Non = -42;
				return;
			}
			
			count = 0;

			while(ReadGPA8)    //读到高电平
			{       
				delay_us(1);
				if(++count > 600)
				{
					Con_Data |= (0x1 << (7 - i));
				}
			}
			if(count > 180){
				Non = -43;
				return;
			}
			count = 0;
			i++;
		}
		
		//检验控制码
		i = 0;
		while(i < 8)
		{
			while(!ReadGPA8)
			{
				delay_us(1);
				if(++count > 600){
					Non = -44;
					return;
				}
			}
			if(count < 400)
			{
				Non = -45;
				return;
			}
			count = 0;

			while(ReadGPA8)
			{		
				delay_us(1);
				if(++count > 600){
					if((Con_Data & (0x1 << (7 - i))) != 0)   //
					{
						Non = -46;
						return;
					}
				}
			}
			
			/*数据码与数据反码相与为0，表示校验成功*/
			if(count < 600 && ((Con_Data & (0x1 << (7 - i))) == 0))
			{
				Non = -47;
				return;
			}
			if(count > 180)
			{
				Non = -48;
				return;
			}
			count = 0;
			i++;
		}
	}
}
