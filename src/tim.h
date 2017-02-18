#ifndef TIM_H_
#define TIM_H_

#define MOTOR_PORT GPIOA
#define MOTOR_PIN_0 GPIO_Pin_0 
#define MOTOR_PIN_1 GPIO_Pin_1
#define MOTOR_PIN_2 GPIO_Pin_2
#define MOTOR_PIN_3 GPIO_Pin_3

#define STEPPER_PORT GPIOD

#define STEPPER_1 GPIO_Pin_14
#define STEPPER_DIR_1 GPIO_Pin_15

#define STEPPER_2 GPIO_Pin_10
#define STEPPER_DIR_2 GPIO_Pin_11

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t ntime);

void INIT_TIM1();
void EnableTimerInterrupt_TIM1();

void INIT_TIM2();
void EnableTimerInterrupt_TIM2();
#endif
