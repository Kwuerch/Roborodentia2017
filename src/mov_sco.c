#include "config.h"
#include "bumper.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"

typedef enum{
    TO_WALL, GOING_TO_WALL, TO_LINE, SCORE_RINGS, ALIGNING, TO_LINE_FRONT, TO_LINE_SCORE, TO_PAST_LINE_SCORE, TO_ALIGN_FRONT, TO_LINE_ALIGN, TO_LINE_RV
}FSM_STATE;

extern int acmer_on;
extern int acmel_on;

STATE_TRANSITION get_supply_pegs_short(){
    static FSM_STATE state = TO_WALL;

    switch( state ){
        case TO_WALL:
            set_score_motor_rot( SERVO_RIGHT_BOUND );

            drive_left_motor( SLOW_FW, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );

            state = GOING_TO_WALL;
            
            break;

        case GOING_TO_WALL:
            if( front_bumper_dep() ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );

                set_score_motor_rot( SERVO_CENTER ); 

                state = TO_LINE;
            }

            break;


        case TO_LINE:
            if( to_past_line_rv_full_skip( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_LEFT_BOUND );

                state = TO_WALL;
                return NEXT;
            }
            break;

        default:
            state = TO_WALL;
            break;
    }

    return CONTINUE;
}

STATE_TRANSITION get_supply_pegs(){
    static FSM_STATE state = TO_LINE_FRONT;
    static int shifted = 0;

    SENSOR_LOC floc = line_loc( LS_FRONT );
    SENSOR_LOC sloc = line_loc2( LS_SCORE ); 
    SENSOR_LOC sploc = line_loc2( LS_SUPPLY );

    switch( state ){
        case TO_LINE_FRONT:
            set_score_motor_rot( SERVO_RIGHT_BOUND );

            drive_left_motor( SLOW_FW, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );

            state = TO_ALIGN_FRONT;
            
            break;

        case TO_ALIGN_FRONT:
            if( !shifted ){
                if( floc == RIGHT ){
                    drive_right_motor( FAST_RV, NORMAL );
                    drive_left_motor( FAST_FW, NORMAL );
                    shifted = 1;
                }else if( floc == LEFT ){
                    drive_right_motor( FAST_FW, NORMAL );
                    drive_left_motor( FAST_RV, NORMAL );
                    shifted = 1;
                }
            }

            if( floc == FULL ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );

                shifted = 0;
                state = TO_LINE_SCORE;
            }

            break;

        case TO_LINE_SCORE:
            if( !shifted ){
                if( sloc == RIGHT ){
                    drive_right_motor( SLOW_RV, NORMAL );
                    drive_left_motor( FAST_FW, NORMAL );
                    shifted = 1;
                }else if( sloc == LEFT ){
                    drive_right_motor( FAST_FW, NORMAL );
                    drive_left_motor( SLOW_RV, NORMAL );
                    shifted = 1;
                }
            }

            if( sloc == FULL ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );

                shifted = 0;
                state = TO_PAST_LINE_SCORE;
            }

            break;

        case TO_PAST_LINE_SCORE:
            if( sloc == EMPTY ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );

                state = TO_LINE_ALIGN;
            }

            break;

        case TO_LINE_ALIGN:
            if( !shifted ){
                if( sploc == RIGHT ){
                    drive_center_motor( SLOW_FW, NORMAL );
                    shifted = 1;
                }else if( sploc == LEFT ){
                    drive_center_motor( SLOW_RV, NORMAL );
                    shifted = 1;
                }
            }

            if( sploc == FULL ){
                drive_center_motor( STOPPED, NORMAL );

                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );

                shifted = 0;
                state = TO_WALL;
            }

            break;

        case TO_WALL:
            if( front_bumper_dep() ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );

                set_score_motor_rot( SERVO_CENTER ); 

                state = TO_LINE_RV;
            }

            break;

        case TO_LINE_RV:
            if( to_past_line_rv_full_skip( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_LEFT_BOUND );

                state = TO_LINE_FRONT;
                return NEXT;
            }

            break;

        default:
            state = TO_LINE_FRONT;
            shifted = 0;
            break;
    }

    /**
    switch( state ){
        case TO_WALL:
            set_score_motor_rot( SERVO_RIGHT_BOUND );

            drive_left_motor( SLOW_FW, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );

            state = ALIGNING;
            
            break;

        case ALIGNING:
            if( !shifted ){
                if( loc == RIGHT ){
                    drive_right_motor( FAST_RV, NORMAL );
                    drive_left_motor( FAST_FW, NORMAL );
                    shifted = 1;
                }else if( loc == LEFT ){
                    drive_right_motor( FAST_FW, NORMAL );
                    drive_left_motor( FAST_RV, NORMAL );
                    shifted = 1;
                }
            }

            if( loc == FULL ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );

                shifted = 0;
                state = GOING_TO_WALL;
            }

            break;

        case GOING_TO_WALL:
            if( front_bumper_dep() ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );

                set_score_motor_rot( SERVO_CENTER ); 

                state = TO_LINE;
            }

            break;


        case TO_LINE:
            if( to_past_line_rv_full_skip( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_LEFT_BOUND );

                state = TO_WALL;
                return NEXT;
            }
            break;

        default:
            state = TO_WALL;
            shifted = 0;
            break;
    }
    **/

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

                state = TO_WALL;
                return NEXT;
            }

            break;


            /**
        case TO_LINE:
            if( align_to_center_pegsr() == NEXT ){
                set_score_motor_rot( SERVO_RIGHT_BOUND );
                state = TO_WALL;
                return NEXT;
            }

            if( to_past_line_rv_full( LS_FRONT ) == NEXT ){
                set_score_motor_rot( SERVO_RIGHT_BOUND );
                state = TO_WALL;
                return NEXT;
            }
            
            break;
            **/

        default:
            state = TO_WALL;
            motors_on = 0;
            break;
    }

    return CONTINUE;
}
