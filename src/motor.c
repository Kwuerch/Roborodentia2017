#include "motor.h"
#include "gpio.h"
#include "tim.h"
#include "config.h"

extern int clock_count_l;
extern int clock_count_r;

extern int acmel_on;
extern int acmer_on;

void init_drive_motors(){
    GPIO_INIT( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR | RIGHT_DRIVE_MOTOR | CENTER_DRIVE_MOTOR | LEFT_DRIVE_MOTOR_DIR | RIGHT_DRIVE_MOTOR_DIR | CENTER_DRIVE_MOTOR_DIR | SERVO_1 );

    INIT_TIM1();
    EnableTimerInterrupt_TIM1();

    INIT_TIM3();
    EnableTimerInterrupt_TIM3();

    INIT_TIM4();
    EnableTimerInterrupt_TIM4();
}

void init_score_motors(){
    GPIO_INIT( STEPPER_PORT, STEPPER_L | STEPPER_DIR_L | STEPPER_R | STEPPER_DIR_R | STEPPER_LR_POWER );
    resetPin( STEPPER_PORT, STEPPER_L | STEPPER_DIR_L | STEPPER_R | STEPPER_DIR_R | STEPPER_LR_POWER );

    INIT_TIM2();
    EnableTimerInterrupt_TIM2();

    INIT_TIM6();
    EnableTimerInterrupt_TIM6();
}

void drive_left_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms ){
    if( mss == STOPPED ){
        resetPin( DRIVE_MOTOR_PORT, LEFT_DRIVE_MOTOR_DIR );
        LEFT_DRIVE_MOTOR_CCR = CCR_ZERO;
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
                LEFT_DRIVE_MOTOR_CCR = MOTOR_SPEED_SLOW + MOTOR_TURNING_DIFF;
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
        RIGHT_DRIVE_MOTOR_CCR = CCR_ZERO;
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

void drive_center_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms ){
    if( mss == STOPPED ){
        resetPin( DRIVE_MOTOR_PORT, CENTER_DRIVE_MOTOR_DIR );
        CENTER_DRIVE_MOTOR_CCR = CCR_ZERO;
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
void drive_score_motor_acmel(int rot){
    setPin( STEPPER_PORT, STEPPER_LR_POWER );
    acmel_on = 1;

    if( rot < 0 ){
        rot *= -1;
        resetPin( STEPPER_PORT, STEPPER_DIR_L );
    }else{
        setPin( STEPPER_PORT, STEPPER_DIR_L );
    }

    clock_count_l = rot * 2;
    TIM2 -> CR1 |= TIM_CR1_CEN;
}

void drive_score_motor_acmer(int rot){
    setPin( STEPPER_PORT, STEPPER_LR_POWER );
    acmer_on = 1;

    if( rot < 0 ){
        rot *= -1;
        resetPin( STEPPER_PORT, STEPPER_DIR_R );
    }else{
        setPin( STEPPER_PORT, STEPPER_DIR_R );
    }

    clock_count_r = rot * 2;
    TIM6 -> CR1 |= TIM_CR1_CEN;
}

// Pos is between 50 and 950
void set_score_motor_rot(int pos){
    SERVO_TIM -> CCR1 =  pos;
}
