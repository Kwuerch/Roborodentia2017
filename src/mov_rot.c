#include "config.h"
#include "line_sensor.h"
#include "mov_rot.h"
#include "motor.h"

typedef enum{
    TO_LINE_REV, TURNING_NO_LINE, TURNING_ON_LINE, START, CENTERED, OVER_RIGHT, OVER_LEFT, WAIT, FROM_CENTER, FROM_WALL, TO_CENTER, TO_WALL, OVER_NONE
}FSM_STATE;

STATE_TRANSITION rotate_left_90(){
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc = line_loc( LS_FRONT );
    switch( state ){
        case CENTERED:
            drive_left_motor( SLOW_RV, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );
            state = TURNING_NO_LINE;
            break;
        case TURNING_NO_LINE:
            if( loc == LEFT ){
                state = TURNING_ON_LINE;
            }
            break;
        case TURNING_ON_LINE:
            if( loc == CENTER ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                state = CENTERED;
                return NEXT;
            }
            break;
        default:
            state = CENTERED;
            break;
    }

    return CONTINUE;
}

STATE_TRANSITION rotate_right_90(){
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc = line_loc( LS_FRONT );
    switch( state ){
        case CENTERED:
            drive_left_motor( SLOW_FW, NORMAL );
            drive_right_motor( SLOW_RV, NORMAL );
            state = TURNING_NO_LINE;
            break;
        case TURNING_NO_LINE:
            if( loc == RIGHT ){
                state = TURNING_ON_LINE;
            }
            break;
        case TURNING_ON_LINE:
            if( loc == CENTER ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                state = CENTERED;
                return NEXT;
            }
            break;
        default:
            state = CENTERED;
            break;
    }

    return CONTINUE;
}
