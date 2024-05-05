#ifndef BSP_RTC_H_
#define BSP_RTC_H_

#include "stm32f10x.h"
#include "bsp_date.h"
#include "digital_led.h"


//�Ƿ�ʹ��LCD��ʾ����
//#define USE_LCD_DISPLAY


//ʹ��LSE�ⲿʱ�� �� LSI�ڲ�ʱ��
#define RTC_CLOCK_SOURCE_LSE      
//#define RTC_CLOCK_SOURCE_LSI

#define RTC_BKP_DRX          BKP_DR1

// д�뵽���ݼĴ��������ݺ궨��
#define RTC_BKP_DATA         0xA5A5

//����ʱ���ʱ��������
#define TIME_ZOOM						(8*60*60)

void RTC_NVIC_Config(void);
void RTC_Configuration(void);
void Time_Regulate_Get(struct rtc_time *tm);
void Time_Adjust(struct rtc_time *tm);
void Time_Display(uint32_t TimeVar,struct rtc_time *tm);
void Time_Show(struct rtc_time *tm);
static uint8_t USART_Scanf(uint32_t value);
void RTC_CheckAndConfig(struct rtc_time *tm);



#endif

