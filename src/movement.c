#include "config.h"
#include "line_sensor.h"
#include "movement.h"
#include "motor.h"

typedef enum{
    TO_LINE_REV, TURNING, START, CENTERED, OVER_RIGHT, OVER_LEFT
}FSM_STATE;


extern uint8_t sensor_c;

STATE_TRANSITION reverse_turn_fsm(){
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

    return CONTINUE;
}

STATE_TRANSITION follow_line_fw(){
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc;

    switch( state ){
        case CENTERED:
            if( (loc = line_loc()) == RIGHT ){
                state = OVER_LEFT;
            }else if( loc == LEFT ){
                state = OVER_RIGHT;
            }else{
                drive_left_motor(50);
                drive_right_motor(50);
            }

            break;
        case OVER_LEFT:
            drive_left_motor(52);
            drive_right_motor(48);
            state = CENTERED;

            /**
            if( (loc = line_loc()) == CENTER ){
                state = CENTERED;
            }else if( loc == LEFT ){
                state = OVER_RIGHT;
            }
            **/
            break;
        case OVER_RIGHT:
            drive_left_motor(48);
            drive_right_motor(52);

            /**
            if( (loc = line_loc()) == CENTER ){
                state = CENTERED;
            }else if( loc == RIGHT ){
                state = OVER_LEFT;
            }
            **/
            state = CENTERED;
            break;
        default:
            state = CENTERED;
    }

    /**
    if( sensor_c & FULL_MASK ){
        return NEXT;
    }
    **/

    return CONTINUE;
}

STATE_TRANSITION follow_line_rv(){
    static FSM_STATE state = CENTERED;

    SENSOR_LOC loc;

    switch( state ){
        case CENTERED:
            if( (loc = line_loc()) == RIGHT ){
                state = OVER_RIGHT;
            }else if( loc == LEFT ){
                state = OVER_LEFT;
            }
            drive_left_motor(-50);
            drive_right_motor(-50);
            break;
        case OVER_LEFT:
            drive_left_motor(-48);
            drive_right_motor(-52);
            state = CENTERED;
            break;
        case OVER_RIGHT:
            drive_left_motor(-52);
            drive_right_motor(-48);
            state = CENTERED;
            break;
        default:
            state = CENTERED;
    }

    if( sensor_c & FULL_MASK ){
        return NEXT;
    }

    return CONTINUE;
}



