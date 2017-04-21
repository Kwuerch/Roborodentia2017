#include "config.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"
#include "mov_lin.h"
#include "mov_rot.h"
#include "mov_sco.h"
#include "bumper.h"

#define ALIGN_DELAY_COUNT 1000

typedef enum{
    TO_LINE_REV, TURNING_NO_LINE, TURNING_ON_LINE, START, CENTERED, OVER_RIGHT, OVER_LEFT, WAIT, FROM_CENTER, FROM_WALL, TO_CENTER, TO_WALL, OVER_NONE, ALIGN_TO_CENTER, SUPPLY, SCORE
}FSM_STATE;

typedef enum{
    TO_LINE, TO_LINE_RV, TO_PAST_LINE, FROM_SIDE, ALIGN_RIGHT, ALIGN_LEFT, ALIGN_DELAY, ALIGN_STOPPED, TO_BEFORE_LINE, ALIGN_PAST_LEFT
}ALIGN_STATE;

// ONLY to be use with 2 light sensor arrays
STATE_TRANSITION to_past_line_fw( LINE_SENSOR_T ls_t ){
    static ALIGN_STATE state = TO_LINE;
    static ALIGN_STATE ps = TO_LINE;
    static int motors_on = 0;

    SENSOR_LOC loc = line_loc2( ls_t );
    switch( state ){
        case TO_LINE:
            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_PAST_LINE;
                ps = TO_LINE;
            }

            break;

        case TO_PAST_LINE:
            if( loc == EMPTY ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                if( ps == TO_LINE ){
                    state = TO_LINE_RV;
                    ps = TO_PAST_LINE;
                    break;
                }else if( ps == TO_LINE_RV ){
                    state = TO_LINE;
                    ps = TO_LINE;
                    return NEXT;
                }
            }

            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            break;

        case TO_LINE_RV:
            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_PAST_LINE;
                ps = TO_LINE_RV;
                break;
            }

            if( !motors_on ){
                drive_left_motor( SLOW_RV, NORMAL );
                drive_right_motor( SLOW_RV, NORMAL );
                motors_on = 1;
            }
            break;
        
        default:
            state = TO_LINE;
            ps = TO_LINE;
            motors_on = 0;
            break;

    }

    return CONTINUE;
}

// ONLY to be use with 2 light sensor arrays
STATE_TRANSITION to_before_line_fw( LINE_SENSOR_T ls_t ){
    static ALIGN_STATE state = TO_LINE;
    static int motors_on = 0;

    SENSOR_LOC loc = line_loc2( ls_t );
    SENSOR_LOC floc = line_loc( LS_FRONT );

    switch( state ){
        case TO_LINE:
            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_BEFORE_LINE;
            }

            break;

        case TO_BEFORE_LINE:
            if( !motors_on ){
                drive_left_motor( SLOW_RV, NORMAL );
                drive_right_motor( SLOW_RV, NORMAL );
                motors_on = 1;
            }

            if( floc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_LINE;
                return NEXT;
            }

            break;
        
        default:
            state = TO_LINE;
            motors_on = 0;
            break;

    }

    return CONTINUE;
}

STATE_TRANSITION to_past_line_fw_full( LINE_SENSOR_T ls_t ){
    static ALIGN_STATE state = TO_LINE;
    static ALIGN_STATE ps = TO_LINE;
    static int motors_on = 0;

    SENSOR_LOC loc = line_loc( ls_t );

    switch( state ){
        case TO_LINE:
            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_PAST_LINE;
                ps = TO_LINE;
            }

            break;

        case TO_PAST_LINE:
            if( loc == RIGHT || loc == LEFT ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                if( ps == TO_LINE ){
                    state = TO_LINE_RV;
                    ps = TO_PAST_LINE;
                    break;
                }else if( ps == TO_LINE_RV ){
                    state = TO_LINE;
                    ps = TO_LINE;
                    return NEXT;
                }
            }

            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            break;

        case TO_LINE_RV:
            if( !motors_on ){
                drive_left_motor( SLOW_RV, NORMAL );
                drive_right_motor( SLOW_RV, NORMAL );
                motors_on = 1;
                break;
            }

            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_PAST_LINE;
                ps = TO_LINE_RV;
            }

            break;
        
        default:
            state = TO_LINE;
            ps = TO_LINE;
            motors_on = 0;
            break;

    }

    return CONTINUE;
}

// ONLY TO be used with full line_sensors
STATE_TRANSITION to_past_line_rv_full( LINE_SENSOR_T ls_t ){
    static ALIGN_STATE state = TO_LINE;
    static ALIGN_STATE ps = TO_LINE;
    static int motors_on = 0;

    SENSOR_LOC loc = line_loc( ls_t );
    switch( state ){
        case TO_LINE:
            if( !motors_on ){
                drive_left_motor( SLOW_RV, NORMAL );
                drive_right_motor( SLOW_RV, NORMAL );
                motors_on = 1;
            }

            if( loc == FULL ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_PAST_LINE;
                ps = TO_LINE;
            }

            break;

        case TO_PAST_LINE:
            if( loc == EMPTY ){
                drive_left_motor( STOPPED, NORMAL );
                drive_right_motor( STOPPED, NORMAL );
                motors_on = 0;

                state = TO_LINE;
                ps = TO_LINE;
                return NEXT;
            }

            if( !motors_on ){
                drive_left_motor( SLOW_FW, NORMAL );
                drive_right_motor( SLOW_FW, NORMAL );
                motors_on = 1;
            }

            break;
        
        default:
            state = TO_LINE;
            ps = TO_LINE;
            motors_on = 0;
            break;

    }

    return CONTINUE;
}
STATE_TRANSITION align_to_center_pegsl(){
    static ALIGN_STATE state = ALIGN_LEFT;
    static ALIGN_STATE ps = ALIGN_DELAY;
    static int count = 0;

    switch( state ){
        case ALIGN_RIGHT:
            if( ps != ALIGN_RIGHT ){
                drive_center_motor( FAST_RV, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_RIGHT;
            break;

        case ALIGN_LEFT:
            if( ps != ALIGN_LEFT ){
                drive_center_motor( FAST_FW, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_LEFT;
            break;
        
        case ALIGN_STOPPED:
            if( ps != ALIGN_STOPPED ){
                drive_center_motor( STOPPED, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_STOPPED;
            break;

        case ALIGN_DELAY:
            if( ++count == ALIGN_DELAY_COUNT ){
                count = 0;
                SENSOR_LOC loc = line_loc( LS_FRONT );

                if( loc == CENTER ){
                    if( ps == ALIGN_STOPPED ){
                        state = ALIGN_LEFT;
                        ps = ALIGN_DELAY;
                        return NEXT;
                    }

                    state = ALIGN_STOPPED;
                
                }else if( loc == RIGHT ){
                    state = ALIGN_RIGHT;
                }else if( loc == LEFT ){
                    state = ALIGN_LEFT;
                }

                // Otherwise Restart Delay Count
            }

            break;
        default:
            state = ALIGN_LEFT;
            ps = ALIGN_DELAY;
            break;
    }

    return CONTINUE;

}

STATE_TRANSITION align_to_center_pegsr(){
    static ALIGN_STATE state = ALIGN_RIGHT;
    static ALIGN_STATE ps = ALIGN_DELAY;
    static int count = 0;

    switch( state ){
        case ALIGN_RIGHT:
            if( ps != ALIGN_RIGHT ){
                drive_center_motor( FAST_RV, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_RIGHT;
            break;

        case ALIGN_LEFT:
            if( ps != ALIGN_LEFT ){
                drive_center_motor( FAST_FW, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_LEFT;
            break;
        
        case ALIGN_STOPPED:
            if( ps != ALIGN_STOPPED ){
                drive_center_motor( STOPPED, NORMAL );
            }

            state = ALIGN_DELAY;
            ps = ALIGN_STOPPED;
            break;

        case ALIGN_DELAY:
            if( ++count == ALIGN_DELAY_COUNT ){
                count = 0;
                SENSOR_LOC loc = line_loc( LS_FRONT );

                if( loc == CENTER ){
                    if( ps == ALIGN_STOPPED ){
                        state = ALIGN_RIGHT;
                        ps = ALIGN_DELAY;
                        return NEXT;
                    }

                    state = ALIGN_STOPPED;
                
                }else if( loc == RIGHT ){
                    state = ALIGN_RIGHT;
                }else if( loc == LEFT ){
                    state = ALIGN_LEFT;
                }

                // Otherwise Restart Delay Count
            }

            break;
        default:
            state = ALIGN_RIGHT;
            ps = ALIGN_DELAY;
            break;
    }

    return CONTINUE;

}

STATE_TRANSITION align_to_pegs( SUP_SCO_ST sss ){
    static ALIGN_STATE state = TO_PAST_LINE; 
    static ALIGN_STATE ps = TO_PAST_LINE;
    static int count = 0;

    if( sss == SCO_ST ){
        switch( state ){
            case TO_PAST_LINE:
                if( to_past_line_fw( LS_SCORE ) == NEXT ){

                    state = ALIGN_LEFT;
                    ps = TO_PAST_LINE;
                }

                break;

            case ALIGN_RIGHT:
                if( ps != ALIGN_RIGHT ){
                    drive_center_motor( FAST_RV, NORMAL );
                }

                state = ALIGN_DELAY;
                ps = ALIGN_RIGHT; 
                break;

            case ALIGN_LEFT:
                if( ps != ALIGN_LEFT ){
                    drive_center_motor( FAST_FW, NORMAL );
                }

                state = ALIGN_DELAY;
                ps = ALIGN_LEFT; 
                
                break;

            case ALIGN_STOPPED:
                if( ps != ALIGN_STOPPED ){
                    drive_center_motor( STOPPED, NORMAL );
                }

                state = ALIGN_DELAY;
                ps = ALIGN_STOPPED;

            case ALIGN_DELAY:
                if( ++count == ALIGN_DELAY_COUNT ){
                    count = 0;

                    SENSOR_LOC loc;
                    // SCORE 
                    loc = line_loc2( LS_SCORE );

                    if( loc == FULL ){
                        if( ps == ALIGN_STOPPED ){
                            state = TO_PAST_LINE;
                            ps = TO_PAST_LINE;
                            return NEXT;
                        }

                        state = ALIGN_STOPPED;
                    
                    }else if( loc == RIGHT ){
                        state = ALIGN_RIGHT;
                    }else if( loc == LEFT ){
                        state = ALIGN_LEFT;
                    }

                    // Otherwise Restart Delay Count
                }

                break;
            default:
                state = TO_PAST_LINE;
                ps = TO_PAST_LINE;
                break;
            }
    }else{

        SENSOR_LOC sploc = line_loc2( LS_SUPPLY );

        switch( state ){
            case TO_PAST_LINE:
                if( to_before_line_fw( LS_SCORE ) == NEXT ){

                    state = ALIGN_LEFT;
                    drive_center_motor( SLOW_FW, NORMAL );

                    ps = TO_PAST_LINE;
                }

                break;

            case ALIGN_LEFT:
                if( sploc == RIGHT ){
                    state = ALIGN_PAST_LEFT;
                }
                
                break;

            case ALIGN_PAST_LEFT:
                if( sploc != RIGHT ){

                    drive_center_motor( SLOW_RV, NORMAL );
                    state = ALIGN_RIGHT;

                }

                break;

            case ALIGN_RIGHT:
                if( sploc == RIGHT ){
                    drive_center_motor( STOPPED, NORMAL );
                    state = TO_PAST_LINE;
                    return NEXT;
                }

                break;

            default:
                state = TO_PAST_LINE;
                break;

            }

    }



    return CONTINUE;
}

STATE_TRANSITION wall_to_cen(){
    static FSM_STATE state = ALIGN_TO_CENTER;

    switch( state ){
        case ALIGN_TO_CENTER:
            if( align_to_center_pegsr() == NEXT ){
                state = TO_CENTER;
            }
            break;

        case TO_CENTER:
            if( follow_line_rv() == NEXT ){
                state = ALIGN_TO_CENTER;
                return NEXT;
            }
            break;
        
        default:
            state = ALIGN_TO_CENTER; 
            break;
    }

    return CONTINUE;
}

STATE_TRANSITION cen_to_wall( SUP_SCO_ST sss ){
    static FSM_STATE state = FROM_CENTER;

    switch( state ){
        case FROM_CENTER:
            if( follow_line_fw() == NEXT ){
                state = TO_WALL;
            }
            break;

        case TO_WALL:
            if( align_to_pegs( sss ) == NEXT ){

                if( sss == SUP_ST ){
                    state = SCORE;
                }else{
                    state = SUPPLY;
                }

            }
            break;

        case SCORE:
            if( get_supply_pegs() == NEXT ){
                state = FROM_CENTER;
                return NEXT;
            }
            break; 

        case SUPPLY:
            if( score_supply_pegs() == NEXT ){
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
