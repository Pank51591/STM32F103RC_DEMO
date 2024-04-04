#ifndef BSP_KEY_H_
#define BSP_KEY_H_

/*key GPIO*/
#include "stm32f10x.h"


#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY1_GPIO_PORT    GPIOC			   
#define    KEY1_GPIO_PIN		 GPIO_Pin_1

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY2_GPIO_PORT    GPIOC		   
#define    KEY2_GPIO_PIN		  GPIO_Pin_13

#define Key1_Read   GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN)
#define Key2_Read   GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN)


#if 0
#define KEY_ON	0      /*Low level detected*/
#define KEY_OFF	1

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

#else
	/*Key Value*/
	#define  Key1   0x01
	#define  Key2   0x02
	#define  Keycom1   0x03
	#define  Key1_3s   0x10
	#define  Key2_3s   0x20

#endif

#define DISPLAY_TIME  0
#define SET_HOUR  1
#define SET_MINUTE 2


void Key_Init(void);
uint8_t Key_Check(void);
void Key_Process(void);

void Time_Set(void);



#endif


