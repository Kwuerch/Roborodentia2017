#ifndef TIM_H_
#define TIM_H_

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t ntime);

void INIT_TIM1();
void EnableTimerInterrupt_TIM1();

void INIT_TIM2();
void EnableTimerInterrupt_TIM2();

void INIT_TIM3();
void EnableTimerInterrupt_TIM3();

void INIT_TIM4();
void EnableTimerInterrupt_TIM4();

void INIT_TIM6();
void EnableTimerInterrupt_TIM6();

#endif
