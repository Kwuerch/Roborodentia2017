#ifndef TIM_H_
#define TIM_H_

#define PWM_RANGE 990

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t ntime);

void INIT_TIM1();
void EnableTimerInterrupt_TIM1();

void INIT_TIM2();
void EnableTimerInterrupt_TIM2();
#endif
