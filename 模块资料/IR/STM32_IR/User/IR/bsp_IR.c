#include "bsp_IR.h"
#include "bsp_usart_dma.h"
#include "sys.h"

int Non = 0;     // Non ��Ҫ�������ԣ����Խ���������һ����־
int Add_Data = 0;
int Con_Data = 0;

//��ʼ������������ж�
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
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;//�������½��ش����ж�
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel				= EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd			= ENABLE;
	/*�����ж����ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority		= 0;
	NVIC_Init(&NVIC_InitStruct);
	
}

/*********************************************************
***��������
***�������ܣ�ͨ���ⲿ�����жϣ����Ժ�����յ����źŽ��н���
***������  Non
***����ֵ��
**********************************************************/
void EXTI9_5_IRQHandler()
{
	int count = 0;
	EXTI_ClearITPendingBit(EXTI_Line8);      //���EXTI���й���λ
	
	printf("%d", Non);   //���Դ���
	
	Non = 0;
//	if(Add_Data != 0 && Con_Data != 0)
//		return;
	
	if(!ReadGPA8)
		{	
		//������9ms�͵�ƽ
		while(!ReadGPA8)   //
		{
			delay_ms(1);
			if(++count > 12)
			{
				Non = -11;
				return;     //����whileѭ��
			}	
		}
		
		if(count < 6)
		{
			Non = -12;
			return;
		}
		count = 0;
		
		//������4.5ms�ߵ�ƽ
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
		
		//��ʼ�������ݲ�����
		GetData();
		
		if(Non != 0)
			return;
		
		//������λ
		
		printf("AData:%d  CData:%d\r\n", Add_Data, Con_Data);
		Non = 0;
	}
	else
	{
		Non = -10;
	}
}

/*********************************************************
***��������GetData
***�������ܣ�
***������
***����ֵ��
**********************************************************/
void GetData()
{
	int count = 0;
	int i = 0;
	
	if(!ReadGPA8){
		//���յ�ַ�뿪ʼ
		Add_Data = 0;
		
		while(i < 8)
		{
			while(!ReadGPA8)    //�����͵�ƽ
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
	
			while(ReadGPA8)   //�����ߵ�ƽ
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
		
		//�����ַ�루���룩
		i = 0;
		while(i < 8)
		{		
			while(!ReadGPA8)  //�����͵�ƽ
			{      
				delay_us(1);
				if(++count > 600)
				{
					Non = -24;
					return;     //����whileѭ��
				}
			}
			if(count < 45){
				Non = -25;
				return;
			}
			
			count = 0;

			while(ReadGPA8)//�����ߵ�ƽ
			{       
				delay_us(1);
				if(++count > 600){
					if((Add_Data & (0x1 << (7 - i))) != 0){
						Non = -31;
						return;
					}
				}
			}
			
			/*��У��ɹ�ʱ�������뷴������Ľ��Ϊ0*/
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
		
		//���տ����뿪ʼ
		Con_Data = 0;
		i = 0;
		while(i < 8)
		{
			while(!ReadGPA8)      //�����͵�ƽ
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

			while(ReadGPA8)    //�����ߵ�ƽ
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
		
		//���������
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
			
			/*�����������ݷ�������Ϊ0����ʾУ��ɹ�*/
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
