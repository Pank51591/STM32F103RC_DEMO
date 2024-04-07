

#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"

#define LED1_PIN                  GPIO_Pin_8                
#define LED1_GPIO_PORT            GPIOA                     

#define LED2_PIN                  GPIO_Pin_2                
#define LED2_GPIO_PORT            GPIOD                   
                    

#define	digitalHi(p,i)			  {p->BSRR=i;}	
#define digitalLo(p,i)			  {p->BSRR=(uint32_t)i << 16;}		
#define digitalToggle(p,i)		{p->ODR ^=i;}	

#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON		    digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF			digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON		    digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF			digitalLo(LED2_GPIO_PORT,LED2_PIN)


#define LED_OFF	   LED1_OFF;LED2_OFF;

void LED_Init(void);



#endif



