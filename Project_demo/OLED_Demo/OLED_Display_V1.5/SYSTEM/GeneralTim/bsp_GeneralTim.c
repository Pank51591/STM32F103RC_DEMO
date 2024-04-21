#include "config.h"

//#include "bsp_GeneralTim.h"
//#include "bsp_usart_dma.h"

u8  IRdatas = 0;                //接收到数据次数
u8  IRval  = 0;                 //接收到的按键值           
u8  RmtCnt = 0;                 //按键重复按下的次数
u8  Remote = 0;                 //遥控按键处理值，全局变量

extern u8 gcPage;
//u8   i;

// 定时器输入捕获用户自定义变量结构体定义
TIM_ICUserValueTypeDef TIM_ICUserValueStructure = {0,0,0,0};

// 中断优先级配置
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输入捕获通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //上拉输入
  GPIO_Init(GENERAL_TIM_CH2_PORT, &GPIO_InitStructure);	
}


///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Capture_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Capture_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(void)
{  
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  // 开启定时器时钟,即内部时钟CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);        //使能TIMx时钟

/*--------------------时基结构体初始化-------------------------*/	
  
	// 自动重装载寄存器的值，累计TIM_Capture_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;	  //
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1) = 1M
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------输入捕获结构体初始化-------------------*/	
	// 配置输入捕获的通道，需要根据具体的GPIO来配置
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_x;    //通道1
	// 输入捕获信号的极性配置
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
	// 输入通道和捕获通道的映射关系，有直连和非直连两种
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// 输入的需要被捕获的信号的分频系数
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// 输入的需要被捕获的信号的滤波系数
	TIM_ICInitStructure.TIM_ICFilter = 0;
	// 定时器输入捕获初始化
	TIM_ICInit(GENERAL_TIM, &TIM_ICInitStructure);
	
	// 清除更新和捕获中断标志位
  TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
  // 开启更新和捕获中断  
	TIM_ITConfig (GENERAL_TIM, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();		
}

TIM_ICUserValueTypeDef TIM_Values;    //初始化结构体 

/*************************************************************
***函数名：GENERAL_TIM_INT_FUN
***函数功能：TIM5的中断   10ms/次
***输入：
***输出：
**************************************************************/
void GENERAL_TIM_INT_FUN(void)                              //定时器x中断服务程序
{
    if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update ) != RESET )     //检查中断是否发生
    {
        if ( TIM_Values.DataFlag == 1 )                 //是否接收到了引导码
        {
            if( TIM_Values.Capture_Period > 3 )              //如果4次溢出中断（40ms）没收到数据，则要么开始收重复码，要么数据收完了
            {
                if( RmtCnt == 0 || TIM_Values.Capture_Period > 9 )                          //如果收到了领导码，且在4次溢出中间没有收到重复码，则判断收完数据，清0标志退出                                                       
                    TIM_Values.DataFlag = 0;                                                //或者收到重复码，且中间90ms没再触发中断，则判断收完数据，清0退出
            }
            TIM_Values.Capture_Period++;
        }
    } 
    if ( TIM_GetITStatus( GENERAL_TIM, GENERAL_TIM_IT_CCx ) != RESET )    //发生了上升沿或者下降沿事件?
    {
        if ( TIM_Values.Capture_StartFlag == 0 )                            //第一次上升沿捕获
        {   
            TIM_SetCounter( GENERAL_TIM, 0 );                               //清0计数器
            GENERAL_TIM_OCxPolarityConfig_FUN( GENERAL_TIM, TIM_ICPolarity_Falling );       //设置为下降沿捕获
            TIM_Values.Capture_CcrValue = 0;                //捕获值清0             
            TIM_Values.Capture_StartFlag = 1;               //开始下降沿捕获
            TIM_Values.Capture_Period = 0;                  //自动重装载寄存器清0
        }
        else  //第二次捕获，下降沿捕获
        {
            TIM_Values.Capture_CcrValue = GENERAL_TIM_GetCapturex_FUN( GENERAL_TIM );//获取TIM5通道2 捕获寄存器的值 （CNT计数的频率1MHZ,即计数1个就是1us）
            GENERAL_TIM_OCxPolarityConfig_FUN( GENERAL_TIM, TIM_ICPolarity_Rising );                        //设置为上升沿捕获
            TIM_Values.Capture_StartFlag = 0;                                   //开始标志复0，重新判断捕获上升沿
            TIM_Values.Capture_FinishFlag = 1;                                  //标记完成1次捕获流程
 
            if ( TIM_Values.Capture_FinishFlag == 1 )         //判断是否完成一次捕获流程
            {
                if ( TIM_Values.DataFlag == 1 )            //是否接收到了引导码
                {
                    if ( TIM_Values.Capture_CcrValue > 300 && TIM_Values.Capture_CcrValue < 800 )           //560为标准值,560us （CNT计数的频率1MHZ,即计数1个就是1us）
                    {
                        TIM_Values.Data <<= 1;                  //左移一位
                        TIM_Values.Data |= 0;                   //接收到0
                        IRdatas++;                      //接收到的数据次数加1.
                    }
                    else if ( TIM_Values.Capture_CcrValue > 1400 && TIM_Values.Capture_CcrValue < 1800 )    //1680为标准值,1680us
                    {
                        TIM_Values.Data <<= 1;                  //左移一位
                        TIM_Values.Data |= 1;                   //接收到1											   
                        IRdatas++;              //接收到的数据次数加1
                    }
										          
                    /*这是 NEC 码规定的110ms连发码(由 9ms 低电平+2.5m 高电平+0.56ms 低电平
                    +97.94ms 高电平组成)，如果在一帧数据发送完毕之后，按键仍然没有放开，则发射重复码，
                    即连发码，可以通过统计连发码的次数来标记按键按下的长短/次数。结束码 ：0.56ms 高电平*/
 
                    else if ( TIM_Values.Capture_CcrValue > 2100 && TIM_Values.Capture_CcrValue < 2500 )    //得到按键键值增加的信息 2250为标准值2.25ms
                    {
                        if( RmtCnt > 3 )            //防止松开慢而误收到重复码，而抛弃前3次收到的重复码 
                            IRdatas++;              //接收到的数据次数加1
                        RmtCnt++;                   //按键次数增加1次  
                    }  
										
//										i  =  TIM_Values.Data;
//										printf ("%d",i);
                }   
                else if ( TIM_Values.Capture_CcrValue > 4200 && TIM_Values.Capture_CcrValue < 4700 )        //4500为标准值4.5ms
                {
                    TIM_Values.DataFlag = 1;            //成功接收到了引导码,数据开始标志为1
                    IRdatas = 0;                        //等于1时收到引导码
                    RmtCnt = 0;                         //清除按键次数计数器
                    
                }
            }
				}
		}
		
		switch ( IRdatas )      
		{
		/*每个遥控器对应一个ID号*/
		//              case 8:     //接收完特征码
		//                  if( TIM_Values.Data != IR_ID )                      //如果接收到的特征码和使用遥控器不相同,则数据全部清0重来
		//                  {
		//                      IRdatas = 0;                    //接收数据次数清0
		//                      TIM_Values.DataFlag = 0;        //开始接收数据标志复位为0  
		//                  }
		//                  TIM_Values.Data = 0;                //接收到的数据清0，只需要数据码
		//                  break;
		// 
		//                case 16:    //接收完特征反码
		//                    //if ( (u8)~TIM_Values.Data != IR_ID )                  //如果知道遥控ID，想只能特定遥控器控制，则用这句与上面一句
		//                    if ( (u8)(TIM_Values.Data>>8) != (u8)~(TIM_Values.Data&0xff) )      //如果特征码和收到的特征反码，比较发现不同，则数据全部清0重来
		//                    {
		//                        IRdatas = 0;                    //接收数据次数清0
		//                        TIM_Values.DataFlag = 0;        //开始接收数据标志复位为0
		//                    }
		//                    TIM_Values.Data = 0;                //接收到的数据清0
		//                    break;

				case 24:    //接收完数据码
						IRval = TIM_Values.Data;        //把数据码存到IRval
						TIM_Values.Data = 0;            //接收到的数据清0，准备接收数据反码
						Remote = IRval;
				
						//printf("Remote = %x\r\n", Remote);
						break;
				

		//                case 32:    //接收完数据反码
		//                    if ( IRval != (u8)~TIM_Values.Data )        //如果数据码和接收到的数据反码不同，则数据码清0,重新开始
		//                    {
		//                        IRdatas = 0;                    //接收数据次数清0
		//                        IRval = 0;                      
		//                    }
		//                    TIM_Values.Data = 0;            //接收到的数据清0，准备接收下一次中断数据
		//                    Remote = IRval;          //把收到的按键值赋值给全局变量 Remote
		//                    IRdatas = 33;            //赋值为33防止在结束码时再进入中断，触发32的判断，导致数据清0
		//                    break;
		//                    
		//                case 34:    //重复码,如果想x个重复码算收到1次重复按键，就把34＋x                  
		//                    Remote = IRval;
		//                    IRdatas = 33;            //重新赋值回33，防止重复按键次数太多，导致数值溢出，且不需要写后面的switch选择
		//                    break;

		} 
////				printf("%d",IRval);
										
				TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	       //清除中断标志位

}


//移植时根据不同的遥控按键值，更改case
void Remote_Scan( uint8_t str )              //遥控按键处理
{        
//    Remote = 0;
    switch( str )
    {
			case 0XA2:    //1
			{
				gcPage = 0;
				printf ("1\r\n");
				 					
			}
					break;
			 case 0X62:   //2
			 {
				 gcPage = 1;
					printf ("2\r\n");
			 }
					break;						
			case 0Xe2:   //3
			{
				gcPage = 2;
					printf ("3\r\n");
			}
					break;
			case 0X22:   //4
			{
					printf ("4\r\n");
			}
					break;
			case 0X2:   //5
			{
					printf ("5\r\n");
			}
					break;
			case 0Xc2:   //6
			{
					printf ("6\r\n");
			}
					break;
			case 0Xe0:   //7
			{
					printf ("7\r\n");
			}
					break;
			case 0Xa8:  //8
			{
					printf ("8\r\n");
			}
					break;
			case 0X90:   //9
			{
					printf ("9\r\n");
			}
					break;
			case 0X98:    //0
			{
					printf ("0\r\n");
			}
					break;					
			case 0X68:    //*
			{
					printf ("*\r\n");
			}
					break;
			case 0Xb0:    //#
			{
					printf ("#\r\n");
			}
					break;
			
			case 0X18:    //上
			 {
				 
				if(gcPage <= PAGE_MAX)
				{
					OLED_Clear();
					gcPage++;		
				}
				else
				{
					gcPage = PAGE0;
				}
				 
					printf ("Up \r\n");
			 }      
					break;
			case 0x10:   //左
			{
				
					printf ("Left\r\n");
			}
					break;
			case 0x38:    //OK
			{
			
					printf ("OK \r\n");
			}
					break;
			case 0x5A:  //右
			{
					printf ("Right\r\n");
			}
					break;
			case 0x4a:  //下
			{
				if(gcPage > PAGE0)
				{
					OLED_Clear();
					gcPage--;		
				}
				else
				{
					gcPage = PAGE_MAX;
				}
				
					printf ("Down\r\n");
			}
					break;   
			default:
					break;
    }
		
		
}

/*********************************************END OF FILE**********************/
