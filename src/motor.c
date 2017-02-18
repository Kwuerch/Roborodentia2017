#include "gpio.h"
#include "tim.h"

extern int clock_count;

void init_drive_motors(){
    GPIO_INIT( MOTOR_PORT, MOTOR_PIN_0 | MOTOR_PIN_1 | MOTOR_PIN_2 | MOTOR_PIN_3 );
    INIT_TIM1();
    EnableTimerInterrupt_TIM1();
}

void init_score_motors(){
    GPIO_INIT( STEPPER_PORT, STEPPER_1 | STEPPER_DIR_1 | STEPPER_2 | STEPPER_DIR_2 );
    resetPin( STEPPER_PORT, STEPPER_1 | STEPPER_DIR_1 | STEPPER_2 | STEPPER_DIR_2 );
    INIT_TIM2();
    EnableTimerInterrupt_TIM2();
}

// Negative Speed means reverse
void drive_left_motor(int speed){

}

void drive_right_motor(int speed){

}

void drive_center_motor(int speed){

}

// Negative Rotation Value means reverse rotation
void drive_score_motor_1(int rot){
    // TODO rot must be less than 500

    if( rot < 0 ){
        rot *= -1;
        setPin( STEPPER_PORT, STEPPER_DIR_1 );
    }else{
        resetPin( STEPPER_PORT, STEPPER_DIR_1 );
    }

    clock_count = rot * 2;
    TIM2 -> CR1 |= TIM_CR1_CEN;
}

void drive_score_motor_2(int rot){


}
