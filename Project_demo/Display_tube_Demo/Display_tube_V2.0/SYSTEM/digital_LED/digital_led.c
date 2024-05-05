#include "config.h"


#define  TUBE_DISPLAY_NULL  26    //不显示

extern uint8_t Key1_3sCount;
extern uint8_t Disp_hour, Disp_minute;

extern struct rtc_time set_time;
//static TM1637_Tube_ts sDisplayData;

//段码表
const uint8_t u8NumTab[] = 
{
	//0,	1,	 2,	 3,  	4,   	5,	  6,   7,  8,   9,    A,   b,  C,   d,   E,   F,  //0., 1.,	2.,	3.,	 4.,  5.,   6.,  7.,  8.,  9. Null
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x00
};

//带时间点的段码
const uint8_t u8NumPoint[] = 
{  //0., 1.,	2.,	3.,	 4.,  5.,   6.,  7.,  8.,  9., Null
	0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x00
};

//最左至最右数码管 ，依次为0-3号，对应的显示寄存器地址
const uint8_t u8TubeAddrTab[] = 
{
	0xC0,0xC1,0xC2,0xC3
};

/*数码管模块 GPIO 配置*/
void Digital_Tube_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*打开APB2时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/**/
	GPIO_InitStructure.GPIO_Pin = TM1637_CLK_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TM1637_CLK_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TM1637_DIO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TM1637_DIO_GPIO_PORT, &GPIO_InitStructure);
	
	
	/*先关显示,给一个停止信号，使设备进入待机状态*/
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x80);
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	
}

void TM1637_I2C_Start(void)
{
	TM1637_CLK(1);
	TM1637_DIO(1); 
	TM1637_DIO(0);
	Delay_us(3);
	TM1637_CLK(0);
}


///============================================= 
void TM1637_I2C_Ask(void)   //1637产生应答 
{
	
	uint8_t P_in;
	TM1637_CLK(0);   //clk = 0; 
	Delay_us(5);     //在第八个时钟下降沿之后延时 5us，开始判断 ACK 信号 
	P_in = TM1673_DIO_READ();
	while(P_in);     //DIO为低电平表示有应答
	TM1637_CLK(1);  //clk = 1; 
	Delay_us(2); 
	TM1637_CLK(0);  //clk=0;
} 


///========================================
void TM1637_I2C_Stop(void) // 1637 停止 
{ 
	 TM1637_CLK(0); //clk = 0; 
	 Delay_us(3);
	 TM1637_DIO(0); //dio = 0; 	 
	 TM1637_CLK(1); //clk = 1; 
	 Delay_us(3); 
	 TM1637_DIO(1); //dio = 1; 
} 

///========================================= 
void TM1637_I2C_WrByte(unsigned char oneByte)   //写一个字节的数据
{ 
	 unsigned char i; 
	 for(i=0;i<8;i++) 
	 { 
		TM1637_CLK(0);     //clk = 0; 
		 if(oneByte&0x01)   //低位在前 
		 { 
			TM1637_DIO(1);   //dio = 1; 
		 } 
		 else 
		 { 
			TM1637_DIO(0);  //dio = 0; 
		 } 
		 Delay_us(3); 
		 oneByte = oneByte>>1; 
		 TM1637_CLK(1);   //clk=1; 
		 Delay_us(3); 
	 } 
} 

#if 0
void TM1637_WriteData(uint8_t Addr,uint8_t Data)
{
	TM1637_I2C_Start();
	TM1637_I2C_WrByte(Addr);
	TM1637_I2C_Ask();
	TM1637_I2C_WrByte(Data);
	TM1637_I2C_Ask();
	TM1637_I2C_Stop();
}

/**数码管显示**/
void TM1637_TubeDisplay(TM1637_Tube_ts sData)
{
	uint8_t temp[4],i;
	temp[0] = u8NumTab[sData.tube0];     //第一位段码值
	temp[1] = u8NumTab[sData.tube1];     //第一位段码值
	temp[2] = u8NumTab[sData.tube2];     //第一位段码值
	temp[3] = u8NumTab[sData.tube3];     //第一位段码值
	for (i=0; i < 4; i++)
	{
			TM1637_WriteData(u8TubeAddrTab[i], temp[i]);
	}
}
#endif


void TM1637_Display(uint8_t Addr,uint8_t Data)
{
	uint8_t SegData;
	if (Addr != 0xc1)
	{
		SegData = u8NumTab[Data];
	}
	else
	{
		if(Count1s_Flag  == 0)
		{
			Set_Count1s_Flag;
			SegData = u8NumPoint[Data];     //显示带点数字
		}
		else
		{
			Clr_Count1s_Flag;
			SegData = u8NumTab[Data];     //显示不带点数字
		}
	}
	
	TM1637_I2C_Start();
	TM1637_I2C_WrByte(0x44);     //固定地址
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	TM1637_I2C_Start();
	TM1637_I2C_WrByte(Addr);
	TM1637_I2C_Ask(); 
	TM1637_I2C_WrByte(SegData);
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	
	TM1637_I2C_Start();
	TM1637_I2C_WrByte(0x8b);     //设置数码管显示亮度
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
}


#if 0
///------------------------------------------------- 
unsigned char ScanKey(void) //读按键 
{ 
	unsigned char rekey,rkey,i; 
	 I2CStart(); 
	 I2CWrByte(0x42); //读按键命令 
	 I2Cask(); 
	 dio=1; // 在读按键前拉高数据线 
	 for(i=0;i<8;i++) //从低位开始读 
	{	clk=0; 
		rekey=rekey>>1;
		Delay_us(30); 
		clk=1; 
		if(dio) 
		{ 
			rekey=rekey|0x80; 
		} 
		else 
		{ 
			rekey=rekey|0x00; 
		} 
		Delay_us(30); 
	 } 
	 I2Cask(); 
	 I2CStop(); 
	 return (rekey); 
}
#endif

#if 0
///================================================ 
void TM1637_SmgDisplay(void) //写显示寄存器 
{ 
//	sDisplayData.tube0 = 1;
//	sDisplayData.tube1 = 2;
//	sDisplayData.tube2 = 3;
//	sDisplayData.tube3 = 4;
	
	// unsigned char i; 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x44);   // 40H 地址自动加 1 模式,44H 固定地址模式, 本程序采用自加 1 模式 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop(); 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0xc0);  //设置首地址， 
	TM1637_I2C_Ask(); 
	
//	for(i=0;i<4;i++)    //地址自加，不必每次都写地址  (这里的地址对应数码管的位数)
//	{ 
//		TM1637_I2C_WrByte(0xb0);    //送数据 
//		TM1637_I2C_Ask(); 
		
//	} 
//	TM1637_TubeDisplay(sDisplayData);
	
	
//	TM1637_I2C_Stop(); 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x8f);   //开显示 ，最大亮度 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop(); 
} 
#endif


#if 0
void Display_init(void)
{
	TM1637_I2C_Start();
	TM1637_I2C_WrByte(0x80);     //关显示
	TM1637_I2C_Ask();
//	TM1637_I2C_Start();
	TM1637_I2C_WrByte(0x8f);     //开显示 ，最大亮度
	TM1637_I2C_Ask();
	TM1637_I2C_Stop(); 
	
	//memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
}
#endif

#if 0
/*******************************************************************************
  * 函数名：Display_TubeDataProcess
  * 功  能：显示数据处理
  * 参  数：无
  * 返回值：无
  * 说  明：4位数码管，根据十进制数据位数，不需要的不显示
*******************************************************************************/
void Display_TubeDataProcess(void)
{
	uint16_t u16Data = 0034;      //需要显示的数据，自定义，或者从其他接口函数获得，本例程直接赋值为1234
//	memset(&sDisplayData, 0xFF, sizeof(sDisplayData));
	
	if (u16Data > 9999)
	{
		u16Data = 9999;  //最多四位数
	}
	if (u16Data > 999)//四位数
	{
		sDisplayData.tube0 = (uint8_t)(u16Data / 1000);//千位
		sDisplayData.tube1 = (uint8_t)(u16Data / 100 % 10);//百位
		sDisplayData.tube2 = (uint8_t)(u16Data % 100 / 10);//十位
	  sDisplayData.tube3 = (uint8_t)(u16Data % 10);//个位
	}else if (u16Data > 99)//三位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL;//不显示
		sDisplayData.tube1 = (uint8_t)(u16Data / 100);//百位
		sDisplayData.tube2 = (uint8_t)(u16Data / 10 % 10);//十位
	  sDisplayData.tube3 = (uint8_t)(u16Data % 10);//个位	   
	}else if (u16Data > 9)//两位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL;//不显示
	  sDisplayData.tube1 = TUBE_DISPLAY_NULL;//不显示
		sDisplayData.tube2 = (uint8_t)(u16Data / 10);//十位
	  sDisplayData.tube3 = (uint8_t)(u16Data % 10);//个位
	}else//一位数
	{
		sDisplayData.tube0 = TUBE_DISPLAY_NULL;//不显示
	  sDisplayData.tube1 = TUBE_DISPLAY_NULL;//不显示
		sDisplayData.tube2 = TUBE_DISPLAY_NULL;//不显示
	  sDisplayData.tube3 = (uint8_t)u16Data;//个位
	}
	TM1637_TubeDisplay(sDisplayData);
}

#endif

void number_Display(void)
{
	
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x44);   // 40H 地址自动加 1 模式,44H 固定地址模式, 本程序采用自加 1 模式 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop(); 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0xc0);  //设置首地址， 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	
	TM1637_Display(0xc0,0);
	TM1637_Display(0xc1,17);    //1.
	TM1637_Display(0xc2,2);
	TM1637_Display(0xc3,4);
}


#if 0
void Digital_Time_Process(struct rtc_time *pm)
{
	uint8_t Hour_Temp = pm->tm_hour;
	uint8_t Minute_Temp = pm->tm_min;
	uint8_t Hour_H,Hour_L,Minute_H,Minute_L;
	
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x44);   // 40H 地址自动加 1 模式,44H 固定地址模式, 本程序采用自加 1 模式 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop(); 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0xc0);  //设置首地址， 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	
	/**/
	Hour_H = Hour_Temp/10;
	Hour_L = Hour_Temp % 10;
	Minute_H = Minute_Temp/10;
	Minute_L = Minute_Temp%10;
	
	/*小时高位*/
	TM1637_Display(0xc0,Hour_H);
	/*小时低位*/
	TM1637_Display(0xc1,Hour_L);
	/*分钟高位*/
	TM1637_Display(0xc2,Minute_H);
	/*分钟低位*/
	TM1637_Display(0xc3,Minute_L);
}
#endif

void Time_DisPlay_Process(struct rtc_time *pm)
{
	uint8_t Hour_Temp = pm->tm_hour;
	uint8_t Minute_Temp = pm->tm_min;
	uint8_t Hour_H,Hour_L,Minute_H,Minute_L;
	
	Hour_H = Hour_Temp/10;
	Hour_L = Hour_Temp%10;
	Minute_H = Minute_Temp/10;
	Minute_L = Minute_Temp%10;
	
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0x44);   // 40H 地址自动加 1 模式,44H 固定地址模式, 本程序采用自加 1 模式 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop(); 
	TM1637_I2C_Start(); 
	TM1637_I2C_WrByte(0xc0);  //设置首地址， 
	TM1637_I2C_Ask(); 
	TM1637_I2C_Stop();
	
	if(DISPLAY_ON_Flag == 0)      //关闭显示
	{
		/*先关显示,给一个停止信号，使设备进入待机状态*/
		TM1637_I2C_Start(); 
		TM1637_I2C_WrByte(0x80);
		TM1637_I2C_Ask(); 
		TM1637_I2C_Stop();
	}
	else
	{
		
		if(Key1_3sCount == SET_HOUR)
		{			
			/*小时高位*/
			TM1637_Display(0xc0,Hour_H);
			/*小时低位*/
			TM1637_Display(0xc1,Hour_L);
			if(Count500ms_Flag)     //500ms闪烁一次
			{
				/*小时高位*/
				TM1637_Display(0xc0,26);     //不显示
				/*小时低位*/
				TM1637_Display(0xc1,10);     //不显示
			}
			/*分钟高位*/
			TM1637_Display(0xc2,Minute_H);
			/*分钟低位*/
			TM1637_Display(0xc3,Minute_L);
			
		}
		else if(Key1_3sCount == SET_MINUTE)
		{
			/*小时高位*/
			TM1637_Display(0xc0,Hour_H);
			/*小时低位*/
			TM1637_Display(0xc1,Hour_L);			
			/*分钟高位*/
			TM1637_Display(0xc2,Minute_H);
			/*分钟低位*/
			TM1637_Display(0xc3,Minute_L);
			if(Count500ms_Flag)     //500ms闪烁一次
			{
				/*小时高位*/
				TM1637_Display(0xc2,26);     //不显示
				/*小时低位*/
				TM1637_Display(0xc3,26);     //不显示
			}
		}
		else    //显示时间
		{
				/*小时高位*/
				TM1637_Display(0xc0,Hour_H);
				/*小时低位*/
				TM1637_Display(0xc1,Hour_L);
				/*分钟高位*/
				TM1637_Display(0xc2,Minute_H);
				/*分钟低位*/
				TM1637_Display(0xc3,Minute_L);
		}
	}
}

#if 1
///======================================= 
void Delay_us(unsigned int i) //nus 延时 
{ 
	 for(;i>0;i--) 
	{
	  __nop(); 
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
			
	}
} 
#endif



