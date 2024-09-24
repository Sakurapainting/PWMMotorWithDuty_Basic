#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//时基单元 由 内部时钟 驱动
	TIM_InternalClockConfig(TIM2);
	
	//初始化时基单元	CK_CNV_OV = CK_CNT/(ARR+1) = CK_PSC/(PSC+1)/(ARR+1)		72M分给PRC,ARR 令CK_CNV_OV = 1(秒)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;					//ARR 自动重装 10K频率下计10000个数即1秒
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;					//PRC 预分频 72M/7200 = 10K计数频率
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				//重复计数器，高级定时器才有，给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// init OC
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	//启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare3(uint16_t Compare){
	TIM_SetCompare3(TIM2, Compare);
}
