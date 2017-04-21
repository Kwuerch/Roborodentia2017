#include "config.h"
#include "bumper.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"

typedef enum{
    TO_WALL, TO_LINE, SCORE_RINGS
}FSM_STATE;

extern int acmer_on;
extern int acmel_on;

STATE_TRANSITION get_supply_pegs(){
    static FSM_STATE state = TO_WALL;
    static int motors_on = 0;

    switch( state ){
        case TO_WALL:
            if( !motors_on ){
                set_score_motor_rot( SERVO_RIGHT_BOUND );
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            if( front_bumper_dep() ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                set_score_motor_rot( SERVO_CENTER ); 

                state = TO_LINE;
            }

            break;

        case TO_LINE:
            if( to_past_line_rv_full( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_LEFT_BOUND );

                state = TO_WALL;
                return NEXT;
            }
            break;

        default:
            state = TO_WALL;
            motors_on = 0;
            break;
    }

    return CONTINUE;
}

STATE_TRANSITION score_supply_pegs(){
    static FSM_STATE state = TO_WALL;
    static int motors_on = 0;

    switch( state ){
        case TO_WALL:
            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            if( front_bumper_dep() ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = SCORE_RINGS;
            }

            break;

        case SCORE_RINGS:
            if( !motors_on ){
                drive_score_motor_acmer( ACMER_ROT_VAL );
                drive_score_motor_acmel( ACMEL_ROT_VAL );
                motors_on = 1;
            }

            if( !acmer_on && !acmel_on ){
                motors_on = 0;
                drive_score_motor_acmer( -1 * ACMER_ROT_VAL );
                drive_score_motor_acmel( -1 * ACMEL_ROT_VAL );
                state = TO_LINE;
            }

            break;

        case TO_LINE:
            if( to_past_line_rv_full( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_RIGHT_BOUND );
                state = TO_WALL;
                return NEXT;
            }
            
            break;

        default:
            state = TO_WALL;
            motors_on = 0;
            break;
    }

    return CONTINUE;
}
