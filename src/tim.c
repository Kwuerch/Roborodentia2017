#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "gpio.h"
#include "tim.h"

__IO uint32_t TimingDelay = 0;

void INIT_TIM1(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = 6;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = 1000;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &time);

    TIM1 -> CCR1 = 200;
    TIM1 -> CCR2 = 400;
    TIM1 -> CCR3 = 600;
    TIM1 -> CCR4 = 800;

    TIM1 -> CCER |= TIM_CCER_CC1E |
                    TIM_CCER_CC2E |
                    TIM_CCER_CC3E |
                    TIM_CCER_CC4E;

    TIM1 -> DIER |= TIM_DIER_UIE |
                    TIM_DIER_CC1IE |
                    TIM_DIER_CC2IE |
                    TIM_DIER_CC3IE |
                    TIM_DIER_CC4IE;

    // Enable Counter
    TIM1 -> CR1  |= TIM_CR1_CEN;
}

void EnableTimerInterrupt_TIM1(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    nvic.NVIC_IRQChannel = TIM1_CC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 3;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void TIM1_UP_TIM16_IRQHandler(){
    if( TIM1 -> SR &= TIM_SR_UIF ){
        TIM1 -> SR &= ~TIM_SR_UIF;
        setPin(MOTOR_PORT, MOTOR_PIN_0 | MOTOR_PIN_1 | MOTOR_PIN_2 | MOTOR_PIN_3 );
    }
}

void TIM1_CC_IRQHandler(){
    if( TIM1 -> SR & TIM_SR_CC1IF ){
        TIM1 -> SR &= ~TIM_SR_CC1IF;
        resetPin(MOTOR_PORT, MOTOR_PIN_0); 
    }

    if( TIM1 -> SR & TIM_SR_CC2IF ){
        TIM1 -> SR &= ~TIM_SR_CC2IF;
        resetPin(MOTOR_PORT, MOTOR_PIN_1); 
    }
    
    if( TIM1 -> SR & TIM_SR_CC3IF ){
        TIM1 -> SR &= ~TIM_SR_CC3IF;
        resetPin(MOTOR_PORT, MOTOR_PIN_2); 
    }
    
    if( TIM1 -> SR & TIM_SR_CC4IF ){
        TIM1 -> SR &= ~TIM_SR_CC4IF;
        resetPin(MOTOR_PORT, MOTOR_PIN_3); 
    }
}

