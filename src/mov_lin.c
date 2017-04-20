#include "config.h"
#include "line_sensor.h"
#include "mov_lin.h"
#include "motor.h"
#include "bumper.h"

typedef enum{
    TO_LINE_REV, TURNING_NO_LINE, TURNING_ON_LINE, START, CENTERED, OVER_RIGHT, OVER_LEFT, WAIT, FROM_CENTER, FROM_WALL, TO_CENTER, TO_WALL, OVER_NONE
}FSM_STATE;

STATE_TRANSITION follow_line_fw(){
    static FSM_STATE ps = CENTERED;
    static FSM_STATE state = CENTERED;

    static int past_line = 0;

    SENSOR_LOC loc = line_loc( LS_FRONT );
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

        case OVER_NONE:
            if( ps == OVER_RIGHT ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( FAST_FW, MOVING );
                ps = OVER_NONE;
                state = WAIT;

            }else if( ps == OVER_LEFT ){
                drive_left_motor( FAST_FW, MOVING );
                drive_right_motor( STOPPED, NORMAL );
                ps = OVER_NONE;
                state = WAIT;
            }            

            break;

        case WAIT:
            switch( loc ){
                case RIGHT:
                    if( ps == OVER_LEFT ){
                        break;
                    }

                    state = OVER_LEFT;
                    break;

                case LEFT:
                    if( ps == OVER_RIGHT ){
                        break;
                    }

                    state = OVER_RIGHT;
                    break;

                case CENTER:
                    if( ps == CENTERED ){
                        break;
                    }

                    state = CENTERED;
                    break;
                    
                case EMPTY:
                    if( ps == OVER_NONE ){
                        break;
                    }

                    state = OVER_NONE;
                    break;

                case FULL:
                    break;
            }
            
            break;

        default:
            state = OVER_NONE;
            break;
    }

    if( loc == FULL ){
        if( past_line ){
            drive_left_motor( STOPPED, NORMAL );
            drive_right_motor( STOPPED, NORMAL );
            ps = CENTERED;
            state = CENTERED;
            past_line = 0;
            return NEXT;
        }
        return CONTINUE;

    }else if( front_bumper_dep() ){
        drive_left_motor( STOPPED, NORMAL );
        drive_right_motor( STOPPED, NORMAL );
        ps = CENTERED;
        state = CENTERED;
        past_line = 0;
        return NEXT;
    }else{
        past_line = 1;
        return CONTINUE;
    }
}

STATE_TRANSITION follow_line_rv(){
    static FSM_STATE ps = CENTERED;
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc = line_loc( LS_BACK );

    switch( state ){
        case CENTERED:
            drive_left_motor( FAST_RV, NORMAL  );
            drive_right_motor( FAST_RV, NORMAL );
            ps = CENTERED;
            state = WAIT;
            break;

        case OVER_LEFT:
            drive_left_motor( FAST_RV, MOVING );
            drive_right_motor( FAST_RV, PIVOT );

            ps = OVER_LEFT;
            state = WAIT;
            break;

        case OVER_RIGHT:
            drive_left_motor( FAST_RV, PIVOT );
            drive_right_motor( FAST_RV, MOVING );

            ps = OVER_RIGHT;
            state = WAIT;
            break;
            
        case WAIT:
            if( loc == LEFT ){
                if( ps != OVER_RIGHT ){
                    state = OVER_RIGHT;
                }
            }else if( loc == RIGHT ){
                if( ps != OVER_LEFT ){
                    state = OVER_LEFT;
                }
            }else{
                if( ps == CENTERED ){
                    state = CENTERED;
                }
            }

            break;

        default:
            state = CENTERED;
    }

    if( loc == FULL ){
        drive_left_motor( STOPPED, NORMAL );
        drive_right_motor( STOPPED, NORMAL );

        state = CENTERED;
        ps = CENTERED;

        return NEXT;
    }

    return CONTINUE;

}
