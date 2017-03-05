#include "config.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"

typedef enum{
    TO_LINE_REV, TURNING, START, CENTERED, OVER_RIGHT, OVER_LEFT, WAIT
}FSM_STATE;


STATE_TRANSITION reverse_turn_fsm(){
    /**
    static FSM_STATE state = TO_LINE_REV;

    switch( state ){
        case TO_LINE_REV:
            drive_left_motor(-50);
            drive_right_motor(-50);

            if( sensor_c & FULL_MASK ){
                drive_left_motor(0);
                drive_right_motor(0);
                state = TURNING;
            }

            break;

        case TURNING:
            drive_left_motor( -50 );
            drive_right_motor( 50 );
            
            if( sensor_c & CENTER_MASK ){
                drive_left_motor( 0 );
                drive_right_motor( 0 );
                state = TO_LINE_REV;
                return NEXT;
            }

            break;

        default:
            state = TO_LINE_REV;

    }
    **/

    return CONTINUE;
}

STATE_TRANSITION follow_line_fw(){
    static FSM_STATE ps = CENTERED;
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc = line_loc();
    switch( state ){
        case CENTERED:
            drive_left_motor( FAST_FW, NORMAL  );
            drive_right_motor( FAST_FW, NORMAL );
            ps = CENTERED;
            state = WAIT;
            break;

        case OVER_LEFT:
            drive_left_motor( FAST_FW, MOVING );
            drive_right_motor( FAST_FW, PIVOT );
            ps = OVER_LEFT;
            state = WAIT;
            break;

        case OVER_RIGHT:
            drive_left_motor( FAST_FW, PIVOT );
            drive_right_motor( FAST_FW, MOVING );
            ps = OVER_RIGHT;
            state = WAIT;
            break;
            
        case WAIT:

            if( loc == RIGHT ){
                if( ps == OVER_LEFT ){
                    break;
                }

                state = OVER_LEFT;
            }else if( loc == LEFT ){
                if( ps == OVER_RIGHT ){
                    break;
                }

                state = OVER_RIGHT;
            }else{
                if( ps == CENTERED ){
                    break;
                }

                state = CENTERED;
            }

            break;

        default:
            state = CENTERED;
    }

    if( loc == FULL ){
        return NEXT;
    }

    return CONTINUE;
}

STATE_TRANSITION follow_line_rv(){
    static FSM_STATE ps = CENTERED;
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc = line_loc();
    switch( state ){
        case CENTERED:
            drive_left_motor( FAST_RV, NORMAL  );
            drive_right_motor( FAST_RV, NORMAL );
            ps = CENTERED;
            state = WAIT;
            break;

        case OVER_LEFT:
            drive_left_motor( FAST_RV, PIVOT );
            drive_right_motor( FAST_RV, MOVING );
            ps = OVER_LEFT;
            state = WAIT;
            break;

        case OVER_RIGHT:
            drive_left_motor( FAST_RV, MOVING );
            drive_right_motor( FAST_RV, PIVOT );
            ps = OVER_RIGHT;
            state = WAIT;
            break;
            
        case WAIT:

            if( loc == LEFT ){
                if( ps == OVER_LEFT ){
                    break;
                }

                state = OVER_LEFT;
            }else if( loc == RIGHT ){
                if( ps == OVER_RIGHT ){
                    break;
                }

                state = OVER_RIGHT;
            }else{
                if( ps == CENTERED ){
                    break;
                }

                state = CENTERED;
            }

            break;

        default:
            state = CENTERED;
    }

    /*
    if( sensor_c & FULL_MASK ){
        return NEXT;
    }
    */

    return CONTINUE;
}



