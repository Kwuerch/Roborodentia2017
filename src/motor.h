#ifndef MOTOR_H_
#define MOTOR_H_

#define DRIVE_MOTOR_PORT GPIOA

#define LEFT_DRIVE_MOTOR_CCR    TIM1 -> CCR1
#define RIGHT_DRIVE_MOTOR_CCR   TIM1 -> CCR2
#define CENTER_DRIVE_MOTOR_CCR  TIM1 -> CCR3

#define LEFT_DRIVE_MOTOR  GPIO_Pin_0 
#define RIGHT_DRIVE_MOTOR GPIO_Pin_1
#define CENTER_DRIVE_MOTOR GPIO_Pin_2

#define LEFT_DRIVE_MOTOR_DIR GPIO_Pin_3
#define RIGHT_DRIVE_MOTOR_DIR GPIO_Pin_4
#define CENTER_DRIVE_MOTOR_DIR GPIO_Pin_5


//#define LEFT_DRIVE_MOTOR_PIN_2 GPIO_Pin_2
//#define LEFT_DRIVE_MOTOR_PIN_3 GPIO_Pin_3

#define STEPPER_PORT GPIOD

#define STEPPER_1 GPIO_Pin_14
#define STEPPER_DIR_1 GPIO_Pin_15

#define STEPPER_2 GPIO_Pin_10
#define STEPPER_DIR_2 GPIO_Pin_11

void init_drive_motors();
void init_score_motors();
void drive_left_motor(int8_t speed);
void drive_right_motor(int8_t speed);
void drive_center_motor(int8_t speed);
void drive_score_motor_1(int rot);
void drive_score_motor_2(int rot);

#endif
