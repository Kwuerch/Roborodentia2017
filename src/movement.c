#include "config.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"
#include "bumper.h"

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
            if( loc == RIGHT ){
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

    static int past_line = 0;

    SENSOR_LOC loc = line_loc( LS_BACK );
    switch( state ){
        case CENTERED:
            drive_left_motor( FAST_RV, NORMAL  );
            drive_right_motor( FAST_RV, NORMAL );
            drive_center_motor( STOPPED, NORMAL );
            ps = CENTERED;
            state = WAIT;
            break;

        case OVER_LEFT:
            drive_left_motor( FAST_RV, MOVING );
            drive_right_motor( FAST_RV, PIVOT );
            drive_center_motor( STOPPED, NORMAL );
            ps = OVER_LEFT;
            state = WAIT;
            break;

        case OVER_RIGHT:
            drive_left_motor( FAST_RV, PIVOT );
            drive_right_motor( FAST_RV, MOVING );
            drive_center_motor( FAST_FW, NORMAL );
            ps = OVER_RIGHT;
            state = WAIT;
            break;
            
        case WAIT:

            if( loc == LEFT ){
                if( ps == OVER_RIGHT ){
                    break;
                }

                state = OVER_RIGHT;
            }else if( loc == RIGHT ){
                if( ps == OVER_LEFT ){
                    break;
                }

                state = OVER_LEFT;
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
        if( past_line ){
            drive_left_motor( STOPPED, NORMAL );
            drive_right_motor( STOPPED, NORMAL );
            drive_center_motor( STOPPED, NORMAL );
            past_line = 0;
            state = CENTERED;
            ps = CENTERED;
            return NEXT;
        }

        return CONTINUE;
    }else{
        past_line = 1;
        return CONTINUE;
    }
}

STATE_TRANSITION wall_to_cen(){
    static FSM_STATE state = TO_WALL;

    switch( state ){
        case TO_WALL:
            if( follow_line_rv() == NEXT ){
                state = TO_CENTER;
            }
            break;

        case TO_CENTER:
            if( follow_line_rv() == NEXT ){
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

STATE_TRANSITION cen_to_wall(){
    static FSM_STATE state = FROM_CENTER;

    switch( state ){
        case FROM_CENTER:
            if( follow_line_fw() == NEXT ){
                state = TO_WALL;
            }
            break;

        case TO_WALL:
            if( follow_line_fw() == NEXT ){
                state = FROM_CENTER;
                return NEXT;
            }
            break;

        default:
            state = FROM_CENTER;
            break;
    }

    return CONTINUE;
}
