#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "gpio.h"
#include "tim.h"
#include "motor.h"

__IO uint32_t TimingDelay = 0;

int clock_count = 0;

void INIT_TIM1(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = 6;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = 1000;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &time);

    TIM1 -> CCR1 = 0; 
    TIM1 -> CCR2 = 0;
    TIM1 -> CCR3 = 0;

    TIM1 -> CCER |= TIM_CCER_CC1E |
                    TIM_CCER_CC2E |
                    TIM_CCER_CC3E;

    TIM1 -> DIER |= TIM_DIER_UIE |
                    TIM_DIER_CC1IE |
                    TIM_DIER_CC2IE |
                    TIM_DIER_CC3IE;

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
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

}

void EnableTimerInterrupt_TIM2(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void INIT_TIM2(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = 140;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = 1000;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &time);

    TIM2 -> DIER |= TIM_DIER_UIE;

    // Enable Counter
    //TIM2 -> CR1 |= TIM_CR1_CEN;
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

        /**
        uint16_t pins = 0;
        if( RIGHT_DRIVE_MOTOR_CCR != 0 ){
            pins |= RIGHT_DRIVE_MOTOR;
        }

        if( LEFT_DRIVE_MOTOR_CCR != 0 ){
            pins |= LEFT_DRIVE_MOTOR;
        }

        if( CENTER_DRIVE_MOTOR_CCR != 0 ){
            pins |= CENTER_DRIVE_MOTOR;
        }

        setPin( DRIVE_MOTOR_PORT, pins );
        **/
        setPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR | CENTER_DRIVE_MOTOR | LEFT_DRIVE_MOTOR );
    }
}

void TIM1_CC_IRQHandler(){
    if( TIM1 -> SR & TIM_SR_CC1IF ){
        TIM1 -> SR &= ~TIM_SR_CC1IF;
        resetPin(DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR); 
    }

    if( TIM1 -> SR & TIM_SR_CC2IF ){
        TIM1 -> SR &= ~TIM_SR_CC2IF;
        resetPin(DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR); 
    }
    
    if( TIM1 -> SR & TIM_SR_CC3IF ){
        TIM1 -> SR &= ~TIM_SR_CC3IF;
        resetPin(DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR); 
    }
}

void TIM2_IRQHandler(){
    static int count = 0;
    
    if( TIM2 -> SR & TIM_SR_UIF ){
        TIM2 -> SR &= ~TIM_SR_UIF;

        count++;
        togglePin( STEPPER_PORT, STEPPER_1 );

        /**
        if( count % 2 ){
            resetPin( STEPPER_PORT, STEPPER_1 );
        }else{
            setPin( STEPPER_PORT, STEPPER_1 );
        }
        **/

        if( count == clock_count ){
            count = 0;
            TIM2 -> CR1 &= ~TIM_CR1_CEN;
        }
    }
}
