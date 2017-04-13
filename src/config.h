#ifndef CONFIG_H_
#define CONFIG_H_

/** Motors **/
#define DRIVE_MOTOR_PORT GPIOC

#define LEFT_DRIVE_MOTOR_CCR    TIM1 -> CCR1
#define RIGHT_DRIVE_MOTOR_CCR   TIM1 -> CCR2
#define CENTER_DRIVE_MOTOR_CCR  TIM1 -> CCR3

#define LEFT_DRIVE_MOTOR  GPIO_Pin_0 
#define RIGHT_DRIVE_MOTOR GPIO_Pin_2
#define CENTER_DRIVE_MOTOR GPIO_Pin_4

#define LEFT_DRIVE_MOTOR_DIR GPIO_Pin_1
#define RIGHT_DRIVE_MOTOR_DIR GPIO_Pin_3
#define CENTER_DRIVE_MOTOR_DIR GPIO_Pin_5


#define STEPPER_PORT GPIOC

#define STEPPER_1 GPIO_Pin_14
#define STEPPER_DIR_1 GPIO_Pin_15

#define STEPPER_2 GPIO_Pin_10
#define STEPPER_DIR_2 GPIO_Pin_11

#define MOTOR_SPEED_FAST 650 
#define MOTOR_SPEED_SLOW 625 

// Pwm diff of right and left from normal speed
#define MOTOR_TURNING_DIFF 100 

// Pwm diff of right - left motors
#define MOTOR_DIFF  -50

/** Bumper **/
#define BUMPER_PORT_CLOCK RCC_AHBPeriph_GPIOB
#define BUMPER_PORT GPIOB

#define BUMPER_PINS GPIO_Pin_0 | GPIO_Pin_1

#define BUMPER_LEFT_PIN GPIO_Pin_0
#define BUMPER_RIGHT_PIN GPIO_Pin_1
#define BUMPER_FRONT (BUMPER_LEFT_PIN | BUMPER_RIGHT_PIN)

/** Line Sensor **/

/** TODO These next two statements need to be the same PORT **/
#define LS_PORT_CLOCK_F_B RCC_AHBPeriph_GPIOD
#define LS_PORT_CLOCK_SC_SP RCC_AHBPeriph_GPIOA

#define LS_PORT_F_B GPIOD
#define LS_PORT_SC_SP GPIOA

#define LS_FRONT_PINS GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15

#define LS_BACK_PINS GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

#define LS_SCORE_PINS GPIO_Pin_0 | GPIO_Pin_1
#define LS_SUPPLY_PINS GPIO_Pin_2 | GPIO_Pin_3

#define FULL_MASK 0xFF
#define EMPTY_MASK 0x00
#define CENTER_MASK 0x18
#define RIGHT_MASK 0x07
#define LEFT_MASK 0xE0

#define FULL_MASK2 0x03
#define RIGHT_MASK2 0x01
#define LEFT_MASK2 0x02

/** Timer **/
#define PWM_RANGE 990

/** Light Wheel **/
#define LED3 GPIO_Pin_9
#define LED4 GPIO_Pin_8
#define LED5 GPIO_Pin_10
#define LED6 GPIO_Pin_15
#define LED7 GPIO_Pin_11
#define LED8 GPIO_Pin_14
#define LED9 GPIO_Pin_12
#define LED10 GPIO_Pin_13

#define LED_PINS LED3 | LED4 | LED5 | LED6 | LED7 | LED8 | LED9 | LED10 

#define LED_PORT GPIOE

#define NUM_LEDS 8

#endif
