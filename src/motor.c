#include "motor.h"
#include "gpio.h"
#include "tim.h"
#include "config.h"

extern int clock_count;

void init_drive_motors(){
    GPIO_INIT( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR | RIGHT_DRIVE_MOTOR | CENTER_DRIVE_MOTOR | LEFT_DRIVE_MOTOR_DIR | RIGHT_DRIVE_MOTOR_DIR | CENTER_DRIVE_MOTOR_DIR );
    INIT_TIM1();
    EnableTimerInterrupt_TIM1();
}

void init_score_motors(){
    GPIO_INIT( STEPPER_PORT, STEPPER_1 | STEPPER_DIR_1 | STEPPER_2 | STEPPER_DIR_2 );
    resetPin( STEPPER_PORT, STEPPER_1 | STEPPER_DIR_1 | STEPPER_2 | STEPPER_DIR_2 );
    INIT_TIM2();
    EnableTimerInterrupt_TIM2();
}

void drive_left_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms ){
    if( mss == STOPPED ){
        resetPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
        LEFT_DRIVE_MOTOR_CCR = 20;
        return;
    }

    if( mss == FAST_RV || mss == SLOW_RV ){
        setPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
    }else{
        resetPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
    }

    if( mss == FAST_FW || mss == FAST_RV ){
        switch( mms ){
            case PIVOT:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_TURNING_DIFF;
                break;
            default:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST;
                break;
        }
        
    }else{
        switch( mms ){
            case PIVOT:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF + MOTOR_TURNING_DIFF;
                break;
            default:
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW;
                break;
        }
    }
}

void drive_right_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms ){
    if( mss == STOPPED ){
        resetPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_DIR );
        RIGHT_DRIVE_MOTOR_CCR = 20;
        return;
    }

    if( mss == FAST_RV || mss == SLOW_RV ){
        setPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_DIR );
    }else{
        resetPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_DIR );
    }

    if( mss == FAST_FW || mss == FAST_RV ){
        switch( mms ){
            case PIVOT:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF + MOTOR_TURNING_DIFF;
                break;
            default:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF;
                break;
        }
        
    }else{
        switch( mms ){
            case PIVOT:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF + MOTOR_TURNING_DIFF;
                break;
            default:
                RIGHT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF;
                break;
        }
    }
}

/**
// Negative Speed means reverse
// speed is given by 100
void drive_left_motor( int8_t speed ){
    if( speed < 0 ){
        speed *= -1;
        setPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
    }else{
        resetPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
    }

    uint16_t ccr = 10 * speed;
    LEFT_DRIVE_MOTOR_CCR = ccr;
}

void drive_right_motor( int8_t speed){
    if( speed < 0 ){
        speed *= -1;
        setPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_DIR );
    }else{
        resetPin( DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_DIR );
    }

    uint16_t ccr = 10 * speed;
    RIGHT_DRIVE_MOTOR_CCR = ccr;
}

**/

void drive_center_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms ){
    if( mss == STOPPED ){
        resetPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR_DIR );
        CENTER_DRIVE_MOTOR_CCR = 20;
        return;
    }

    if( mss == FAST_RV || mss == SLOW_RV ){
        setPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR_DIR );
    }else{
        resetPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR_DIR );
    }

    if( mss == FAST_FW || mss == FAST_RV ){
        switch( mms ){
            case PIVOT:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF + MOTOR_TURNING_DIFF;
                break;
            default:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_FAST + MOTOR_DIFF;
                break;
        }
        
    }else{
        switch( mms ){
            case PIVOT:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF - MOTOR_TURNING_DIFF;
                break;
            case MOVING:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF + MOTOR_TURNING_DIFF;
                break;
            default:
                CENTER_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_DIFF;
                break;
        }
    }
}

// Negative Rotation Value means reverse rotation
void drive_score_motor_1(int rot){
    if( rot < 0 ){
        rot *= -1;
        setPin( STEPPER_PORT, STEPPER_DIR_1 );
    }else{
        resetPin( STEPPER_PORT, STEPPER_DIR_1 );
    }

    clock_count = rot * 2;
    TIM2 -> CR1 |= TIM_CR1_CEN;
}

// TODO
void drive_score_motor_2(int rot){


}
