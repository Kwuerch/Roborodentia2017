#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "gpio.h"
#include "tim.h"
#include "motor.h"
#include "config.h"

__IO uint32_t TimingDelay = 0;

int clock_count_l = 0;
int clock_count_r = 0;

int acmel_on = 0;
int acmer_on = 0;

void INIT_TIM1(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = TIM_LR_PRESCALE; 
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = TIM_PERIOD;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &time);

    TIM1 -> CCR1 = 0; 
    TIM1 -> CCR2 = 0;

    TIM1 -> CCER |= TIM_CCER_CC1E |
                    TIM_CCER_CC2E;

    TIM1 -> DIER |= TIM_DIER_UIE |
                    TIM_DIER_CC1IE |
                    TIM_DIER_CC2IE;

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


// ACME STEPPER LEFT TIMER
void INIT_TIM2(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = TIM_STEPPER_PRESCALE;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = TIM_PERIOD;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &time);

    TIM2 -> DIER |= TIM_DIER_UIE;
}

void EnableTimerInterrupt_TIM2(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

// ACME STEPPER RIGHT TIMER
void INIT_TIM6(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = TIM_STEPPER_PRESCALE;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = TIM_PERIOD;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM6, &time);

    TIM6 -> DIER |= TIM_DIER_UIE;
}

void EnableTimerInterrupt_TIM6(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void INIT_TIM3(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = TIM_C_PRESCALE;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = TIM_PERIOD;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &time);

    TIM3 -> CCR1 = CCR_ZERO; 

    TIM3 -> CCER |= TIM_CCER_CC1E;

    TIM3 -> DIER |= TIM_DIER_UIE |
                    TIM_DIER_CC1IE;

    // Enable Counter
    TIM3 -> CR1  |= TIM_CR1_CEN;
}

void EnableTimerInterrupt_TIM3(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void INIT_TIM4(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef time;

    time.TIM_Prescaler = TIM_SERVO_PRESCALE;
    time.TIM_CounterMode = TIM_CounterMode_Up;
    time.TIM_Period = TIM_SERVO_PERIOD;
    time.TIM_ClockDivision = TIM_CKD_DIV1;
    time.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &time);

    TIM4 -> CCR1 = SERVO_RIGHT_BOUND; 
    TIM4 -> CCR2 = SERVO_FLAG_RIGHT_BOUND; 

    TIM4 -> CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;

    TIM4 -> DIER |= TIM_DIER_UIE |
                   TIM_DIER_CC1IE |
                   TIM_DIER_CC2IE;

    // Enable Counter
    TIM4 -> CR1  |= TIM_CR1_CEN;
}

void EnableTimerInterrupt_TIM4(){
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
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
        setPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR | LEFT_DRIVE_MOTOR );
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
}

void TIM2_IRQHandler(){
    static int count = 0;
    
    if( TIM2 -> SR & TIM_SR_UIF ){
        TIM2 -> SR &= ~TIM_SR_UIF;

        count++;
        togglePin( STEPPER_PORT, STEPPER_L );

        if( count == clock_count_l ){
            count = 0;
            acmel_on = 0;

            if( !acmer_on ){
                resetPin( STEPPER_PORT, STEPPER_LR_POWER );
            }

            TIM2 -> CR1 &= ~TIM_CR1_CEN;
        }
    }
}

void TIM3_IRQHandler(){
    if( TIM3 -> SR & TIM_SR_UIF ){
        TIM3 -> SR &= ~TIM_SR_UIF;
        setPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR );
    }else if( TIM3 -> SR & TIM_SR_CC1IF ){
        TIM3 -> SR &= ~TIM_SR_CC1IF;
        resetPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR); 
    }
}

void TIM4_IRQHandler(){
    if( TIM4 -> SR & TIM_SR_UIF ){

        TIM4 -> SR &= ~TIM_SR_UIF;
        setPin( SERVO_PORT, SERVO_1 );
        setPin( SERVO_PORT, SERVO_FLAG );

    }else if( TIM4 -> SR & TIM_SR_CC1IF ){

        TIM4 -> SR &= ~TIM_SR_CC1IF;
        resetPin( SERVO_PORT, SERVO_1 );

    }else if( TIM4 -> SR & TIM_SR_CC2IF ){

        TIM4 -> SR &= ~TIM_SR_CC2IF;
        resetPin( SERVO_PORT, SERVO_FLAG );
    }
}

void TIM6_DAC_IRQHandler(){
    static int count = 0;
    
    if( TIM6 -> SR & TIM_SR_UIF ){
        TIM6 -> SR &= ~TIM_SR_UIF;

        count++;
        togglePin( STEPPER_PORT, STEPPER_R );

        if( count == clock_count_r ){
            count = 0;
            acmer_on = 0;

            if( !acmel_on ){
                resetPin( STEPPER_PORT, STEPPER_LR_POWER );
            }

            TIM6 -> CR1 &= ~TIM_CR1_CEN;
        }
    }
}
