
#include "Tim3.h"

//stm32f10x_tim.h и stm32f10x_tim.c.


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
void TIM3_Int_Init_(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* Clock enable */

    /*TIM3 timer initialization*/
    TIM_TimeBaseStructure.TIM_Period = arr; /*Cycle value*/
    TIM_TimeBaseStructure.TIM_Prescaler = psc; /* Pre frequency value */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*Set the clock division: TDTS = Tck_tim*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM up counting mode*/
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); /*According to the specified parameter initialization of TIMx time base unit*/

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); /*The specified TIM3 interrupt, interrupt is allowed to update*/
    TIM3_NVIC_Init();

    TIM_Cmd(TIM3,ENABLE);/*Enable TIMx*/
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* Clock enable */
  TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_Cmd(TIM3,DISABLE);
    /*TIM3 timer initialization*/
	 psc = (2000-1);//arr = 0xffffffff;
    TIM_TimeBaseStructure.TIM_Period = 0xffffffff|arr; /*Cycle value default= 0xffffffff;*/
    TIM_TimeBaseStructure.TIM_Prescaler = psc; /* Pre frequency value */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; /*Set the clock division: TDTS = Tck_tim*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM up counting mode*/
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); /*According to the specified parameter initialization of TIMx time base unit*/

	/* Output Compare Timing Mode настроювання: Канал:1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1_VAL<<1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE); /*The specified TIM3 interrupt, interrupt is allowed to update*/
//    TIM3_NVIC_Init();
	if(TIM2->CR1 & (TIM_CR1_CEN))
    TIM_Cmd(TIM3,ENABLE);/*Enable TIMx*/
}
void TIM3ReInit(void* pv){
register long i,j;
i = ((TIM3InitInfo*)pv)->shARR;
j = ((TIM3InitInfo*)pv)->shPSC;
//if(chT2Start)
TIM3_Int_Init(i,j);

}
/**
 * Interrupt priority set 3 NVIC
 */
void TIM3_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; /*TIM3 interrupt*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*Preemptive priority level 0*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; /*From the priority level 3*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*The IRQ channel is enabled*/
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * Timer 3 interrupt service routine
 */
 
//= void TIM3_IRQHandler(void)
//= {
//=      TIM3->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
//= 	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET ) /*Check the TIM3 update interrupt occurs or not*/
//=     
//=         TIM_ClearITPendingBit(TIM3, TIM_IT_Update); /*Remove TIMx update interrupt flag */
//=         //LED0 = !LED0;
//=     }
//= //	asm(
//= //    "bkpt 1"
//= //    );
//= }
