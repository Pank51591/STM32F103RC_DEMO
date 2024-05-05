#include "bsp_led.h"

void LED_Init(void)
{		 
    GPIO_InitTypeDef  GPIO_InitStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);	 //¿ªGPIOÊ±ÖÓ
	
    GPIO_InitStruct.GPIO_Pin = (LED1_PIN | LED2_PIN);	
   
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;  
   
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);	 															      	
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
	
//    LED_OFF;
		LED1_ON;
	  LED2_OFF;
}
