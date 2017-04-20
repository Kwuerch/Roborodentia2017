#include "config.h"
#include "line_sensor.h"
#include "mov_rot.h"
#include "motor.h"

typedef enum{
    TURNING_OFF_LINE, TURNING_TO_LINE, TURNING_ON_LINE, CENTERED, ALIGN_TO_LINE
}FSM_STATE;

STATE_TRANSITION rotate_left_90(){
    static FSM_STATE state = CENTERED;

    SENSOR_LOC bloc = line_loc( LS_BACK );
    SENSOR_LOC floc = line_loc( LS_FRONT );
    SENSOR_LOC sploc = line_loc2( LS_SUPPLY );

    switch( state ){
        case CENTERED:
            drive_left_motor( SLOW_RV, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );
            state = TURNING_OFF_LINE;
            break;

        case TURNING_OFF_LINE:
            if( sploc == LEFT ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                state = ALIGN_TO_LINE;
            }
            break;

        case ALIGN_TO_LINE:
            // TODO **** Change ALIGN TO CENTER TO go EITHER RIGHT or LEFT ****** TODO //
            if( align_to_center_pegsl() == NEXT ){
                state = CENTERED;
                return NEXT;
            }
            break;

        /**
        case CENTERED:
            drive_left_motor( SLOW_RV, NORMAL );
            drive_right_motor( SLOW_FW, NORMAL );
            state = TURNING_OFF_LINE;
            break;

        case TURNING_OFF_LINE:
            if( floc == RIGHT || bloc == LEFT ){
                state = TURNING_TO_LINE;
            }

            break;

        case TURNING_TO_LINE:
            if( floc == LEFT || bloc == CENTER ){
                drive_right_motor( STOPPED, NORMAL );
                state = TURNING_ON_LINE;
            }
            break;

        case TURNING_ON_LINE:
            if( floc == CENTER ){
                drive_left_motor( STOPPED, NORMAL );
                state = CENTERED;
                return NEXT;

            }
            break;
        **/

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
            state = TURNING_TO_LINE;
            break;
        case TURNING_TO_LINE:
            if( loc == RIGHT ){
                drive_left_motor( STOPPED, NORMAL );
                state = TURNING_ON_LINE;
            }
            break;
        case TURNING_ON_LINE:
            if( loc == CENTER ){
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
