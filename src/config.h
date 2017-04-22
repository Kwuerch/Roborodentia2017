#ifndef CONFIG_H_
#define CONFIG_H_

/** Motors **/
#define DRIVE_MOTOR_PORT GPIOC

#define LEFT_DRIVE_MOTOR_CCR    TIM1 -> CCR1
#define RIGHT_DRIVE_MOTOR_CCR   TIM1 -> CCR2
#define CENTER_DRIVE_MOTOR_CCR  TIM3 -> CCR1

#define SERVO_LEFT_BOUND 570
#define SERVO_RIGHT_BOUND 950 
#define SERVO_CENTER  850 

#define CCR_ZERO 5 
#define TIM_PERIOD 1000
#define TIM_SERVO_PERIOD 10000

#define TIM_C_PRESCALE 40
#define TIM_LR_PRESCALE 12 
#define TIM_STEPPER_PRESCALE 100
#define TIM_SERVO_PRESCALE   143

#define LEFT_DRIVE_MOTOR  GPIO_Pin_0 
#define RIGHT_DRIVE_MOTOR GPIO_Pin_2
#define CENTER_DRIVE_MOTOR GPIO_Pin_4

#define LEFT_DRIVE_MOTOR_DIR GPIO_Pin_1
#define RIGHT_DRIVE_MOTOR_DIR GPIO_Pin_3
#define CENTER_DRIVE_MOTOR_DIR GPIO_Pin_5

#define ACMEL_TIM TIM2
#define ACMER_TIM TIM5

#define ACMER_ROT_VAL 1035 
#define ACMEL_ROT_VAL 980

#define STEPPER_PORT GPIOC

#define STEPPER_LR_POWER GPIO_Pin_11 

#define STEPPER_L GPIO_Pin_14
#define STEPPER_DIR_L GPIO_Pin_15

#define STEPPER_R GPIO_Pin_6
#define STEPPER_DIR_R GPIO_Pin_7

#define SERVO_PORT GPIOC

#define SERVO_1 GPIO_Pin_8
#define SERVO_TIM TIM4

#define MOTOR_SPEED_FAST 750 
#define MOTOR_SPEED_SLOW 700 

// Pwm diff of right and left from normal speed
//#define MOTOR_TURNING_DIFF 30 
#define MOTOR_TURNING_DIFF 50

// Pwm diff of right - left motors
#define MOTOR_DIFF  -50

/** Bumper **/
#define BUMPER_PORT_CLOCK RCC_AHBPeriph_GPIOB
#define BUMPER_PORT GPIOB

#define BUMPER_PINS GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_13

#define BUMPER_LEFT_PIN_F GPIO_Pin_0
#define BUMPER_RIGHT_PIN_F GPIO_Pin_1

#define BUMPER_LEFT_PIN_B GPIO_Pin_12
#define BUMPER_RIGHT_PIN_B GPIO_Pin_13

#define BUMPER_FRONT (BUMPER_LEFT_PIN_F | BUMPER_RIGHT_PIN_F )

#define BUMPER_BACK (BUMPER_LEFT_PIN_B | BUMPER_RIGHT_PIN_B )

/** Line Sensor **/

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

#define TURN_DELAY_LONG 1500
#define TURN_DELAY_SHORT 750
#define LEFT_RIGHT_ALIGNMENT_DELAY 750

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
