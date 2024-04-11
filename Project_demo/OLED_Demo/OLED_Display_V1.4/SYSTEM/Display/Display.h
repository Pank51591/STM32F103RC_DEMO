#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "stm32f10x.h"

enum Page_NUM
{
	PAGE0 = 0,
	PAGE1,
	PAGE2,
	PAGE3,
	PAGE4,
	PAGE_MAX = PAGE4
};



void Display_Update (void);

void Disp_Page1(void);
void Disp_Page2(void);
void Disp_Page3(void);


#endif
