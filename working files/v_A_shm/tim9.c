#include "Tim9.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../inc/constants.h"

#include "stm32f2xx.h"
#include "hw_config.h"
#include "platform_config.h"
#include "header.h"

//stm32f10x_tim.h и stm32f10x_tim.c.
long lInterval = 0;
void TIM9_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//uint16_t TIM_Prescaler
//uint16_t TIM_CounterMode
//uint32_t TIM_Period
//uint16_t TIM_ClockDivision
//uint8_t TIM_RepetitionCounter

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	//-*Cycle value*-/
	TIM_TimeBaseStructure.TIM_Period = 0xffff;  
	//-* Pre frequency value *-/
	TIM_TimeBaseStructure.TIM_Prescaler = 10;//Max precision? or may 1 for extend diapason 
	//-*Set the clock division: TDTS = Tck_tim*-/  
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //Means 00: tDTS = tCK_INT
	//-* TIM up counting mode*-/
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//-*According to the specified parameter initialization of TIMx time base unit*-/
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); 
	DBGMCU_APB2PeriphConfig(DBGMCU_TIM9_STOP, ENABLE);
}
void TIM9Start(void){
TIM_Cmd(TIM9,ENABLE);/*Enable TIMx*/
}
void TIM9Stop(void){
TIM_Cmd(TIM9,DISABLE);

}
/**
 * General purpose timer 3 interrupt initialization
 * This clock is 2 times of that of APB1, while APB1 is 36M
 * arr: Automatic reload value. 
 * psc: The frequency of the clock Prescaler
 * The calculation formula is as follows: 
 * Tout= ((arr+1)*(psc+1))/Tclk, 
 * Among them: 
 * Tclk: The input clock frequency TIM3 (unit: Mhz). 
 * Tout: TIM3 overflow time (unit: US). 
 */
//void TIM3_Int_Init_(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* Clock enable */
//
//    /*TIM3 timer initialization*/
//    TIM_TimeBaseStructure.TIM_Period = arr; /*Cycle value*/
//    TIM_TimeBaseStructure.TIM_Prescaler = psc; /* Pre frequency value */
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*Set the clock division: TDTS = Tck_tim*/
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM up counting mode*/
//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); /*According to the specified parameter initialization of TIMx time base unit*/
//
//    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); /*The specified TIM3 interrupt, interrupt is allowed to update*/
//    TIM3_NVIC_Init();
//
//    TIM_Cmd(TIM3,ENABLE);/*Enable TIMx*/
//}

//void TIM3_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* Clock enable */
//  TIM_OCInitTypeDef  TIM_OCInitStructure;
//TIM_Cmd(TIM3,DISABLE);
//    /*TIM3 timer initialization*/
//	 psc = (2000-1);//arr = 0xffffffff;
//    TIM_TimeBaseStructure.TIM_Period = 0xffffffff|arr; /*Cycle value default= 0xffffffff;*/
//    TIM_TimeBaseStructure.TIM_Prescaler = psc; /* Pre frequency value */
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0; /*Set the clock division: TDTS = Tck_tim*/
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM up counting mode*/
//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); /*According to the specified parameter initialization of TIMx time base unit*/
//
//	/* Output Compare Timing Mode настроювання: Канал:1 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
//	TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1_VAL<<1;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
//
//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
//	
//    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE); /*The specified TIM3 interrupt, interrupt is allowed to update*/
////    TIM3_NVIC_Init();
//	if(TIM2->CR1 & (TIM_CR1_CEN))
//    TIM_Cmd(TIM3,ENABLE);/*Enable TIMx*/
//}
/*
void TIM9ReInit(void* pv){
register long i,j;
i = ((TIM3InitInfo*)pv)->shARR;
j = ((TIM3InitInfo*)pv)->shPSC;
	void(i+j);
//if(chT2Start)
//TIM3_Int_Init(i,j);

}
*/
/**
 * Interrupt priority set 3 NVIC
 */
//void TIM3_NVIC_Init(void)
//{
//    NVIC_InitTypeDef NVIC_InitStructure;
//    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; /*TIM3 interrupt*/
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*Preemptive priority level 0*/
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; /*From the priority level 3*/
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*The IRQ channel is enabled*/
//    NVIC_Init(&NVIC_InitStructure);
//}
