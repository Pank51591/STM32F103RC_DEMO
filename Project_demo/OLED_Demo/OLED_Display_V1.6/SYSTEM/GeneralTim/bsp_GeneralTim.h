#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM5

#define            GENERAL_TIM                   TIM5
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM5
#define            GENERAL_TIM_PERIOD           (10000-1)
#define            GENERAL_TIM_PSC              (72-1)

// TIM 输入捕获通道GPIO相关宏定义
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_1
#define            GENERAL_TIM_CHANNEL_x         TIM_Channel_2

// 中断相关宏定义
#define            GENERAL_TIM_IT_CCx            TIM_IT_CC2       //捕获比较中断  1~4
#define            GENERAL_TIM_IRQ               TIM5_IRQn
#define            GENERAL_TIM_INT_FUN           TIM5_IRQHandler

// 获取捕获寄存器值函数宏定义
#define            GENERAL_TIM_GetCapturex_FUN                 TIM_GetCapture2
// 捕获信号极性函数宏定义
#define            GENERAL_TIM_OCxPolarityConfig_FUN           TIM_OC2PolarityConfig       //配置TIMx通道1极性


#define            NVIC_PriorityGroup_x       NVIC_PriorityGroup_0         //设置中断组0

// 测量的起始边沿
#define            GENERAL_TIM_STRAT_ICPolarity                TIM_ICPolarity_Rising
// 测量的结束边沿
#define            GENERAL_TIM_END_ICPolarity                  TIM_ICPolarity_Falling




// 定时器输入捕获用户自定义变量结构体声明
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志,产生了多少次中断
	uint8_t   DataFlag;             // 收到引导码标志
  uint16_t  Data;                 // 接收到的数据
}  TIM_ICUserValueTypeDef;

//extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

/**************************函数声明********************************/
void GENERAL_TIM_Init(void);


void Remote_Scan( uint8_t str );


#endif	/* __BSP_GENERALTIME_H */


