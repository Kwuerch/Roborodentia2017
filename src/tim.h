#ifndef TIM_H_
#define TIM_H_

#define MOTOR_PORT GPIOE
#define MOTOR_PIN_0 GPIO_Pin_8 | GPIO_Pin_12 
#define MOTOR_PIN_1 GPIO_Pin_1
#define MOTOR_PIN_2 GPIO_Pin_2
#define MOTOR_PIN_3 GPIO_Pin_3

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t ntime);

void INIT_TIM1();
void EnableTimerInterrupt_TIM1();

#endif
