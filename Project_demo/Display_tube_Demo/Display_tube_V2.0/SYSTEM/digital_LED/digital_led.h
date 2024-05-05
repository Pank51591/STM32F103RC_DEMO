#ifndef DIGITAL_LED_H_
#define DIGITAL_LED_H_

#include "stm32f10x.h"
#include "bsp_date.h"

/**/
#define  TM1637_CLK_GPIO_PORT  GPIOA
#define  TM1637_CLK_GPIO_PIN   GPIO_Pin_12
   
#define  TM1637_DIO_GPIO_PORT  GPIOA
#define  TM1637_DIO_GPIO_PIN   GPIO_Pin_11


/**/
#define TM1637_CLK(a) if(a) GPIO_SetBits(TM1637_CLK_GPIO_PORT,TM1637_CLK_GPIO_PIN);\
												else  GPIO_ResetBits(TM1637_CLK_GPIO_PORT,TM1637_CLK_GPIO_PIN);
	
#define TM1637_DIO(b) if(b) GPIO_SetBits(TM1637_DIO_GPIO_PORT,TM1637_DIO_GPIO_PIN);\
												else  GPIO_ResetBits(TM1637_DIO_GPIO_PORT,TM1637_DIO_GPIO_PIN);
												
#define TM1673_DIO_READ()   GPIO_ReadInputDataBit(TM1637_DIO_GPIO_PORT,TM1637_DIO_GPIO_PIN)       //((TM1637_DIO_GPIO_PORT->IDR & TM1637_DIO_GPIO_PIN) != 0)


typedef struct 
{
	uint8_t tube0;
	uint8_t tube1;
	uint8_t tube2;
	uint8_t tube3;
}TM1637_Tube_ts;

void Digital_Tube_Config(void);
void TM1637_I2C_Start(void);
void TM1637_I2C_Ask(void);
void TM1637_I2C_Stop(void);
void TM1637_I2C_WrByte(unsigned char oneByte);
void TM1637_WriteData(uint8_t Addr,uint8_t Data);
void TM1637_SmgDisplay(void);
void Delay_us(unsigned int i);
//void TM1637_TubeDisplay(TM1637_Tube_ts sData);
void Display_TubeDataProcess(void);
void Display_init(void);
void TM1637_Display(uint8_t Addr,uint8_t Data);
void number_Display(void);
void Digital_Time_Process(struct rtc_time *pm);
void Time_DisPlay_Process(struct rtc_time *pm);

#endif

