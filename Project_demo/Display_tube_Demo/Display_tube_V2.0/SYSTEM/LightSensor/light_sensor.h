#ifndef __LIGHT_SENSOR_H__
#define __LIGHT_SENSOR_H__


#define    LSD_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    LSD_GPIO_PORT    GPIOA			   
#define    LSD_GPIO_PIN		  GPIO_Pin_2

#define    LSA_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    LSA_GPIO_PORT    GPIOA			   
#define    LSA_GPIO_PIN		  GPIO_Pin_2


#include "stm32f10x.h"

// ADC 编号选择
// 可以是 ADC1/2，如果使用ADC3，中断相关的要改成ADC3的
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

//// ADC GPIO宏定义
//// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
//#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
//#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
//#define    ADC_PORT                      GPIOA
//#define    ADC_PIN                       GPIO_Pin_2

// ADC 通道宏定义
#define    ADC_CHANNEL                   ADC_Channel_2

// ADC 中断相关宏定义
#define    ADC_IRQ                       ADC1_2_IRQn
#define    ADC_IRQHandler                ADC1_2_IRQHandler

//#define    ADC_IRQ                       ADC3_IRQn
//#define    ADC_IRQHandler                ADC3_IRQHandler


void ADCx_Init(void);



#endif
