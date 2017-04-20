#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"
#include "light_wheel.h"
#include "motor.h"
#include "movement.h"
#include "mov_lin.h"
#include "mov_rot.h"
#include "bumper.h"
#include "config.h"

RCC_ClocksTypeDef RCC_Clocks;

extern uint8_t sensor_c;
extern uint16_t sensor_lr;

typedef enum{
    WALL_TO_CEN, ROT_RT_90, ROT_LF_90, CEN_TO_WALL
}FSM_STATE;

int test_line_sensor( LINE_SENSOR_T lss){
    while( 1 ){
        test_line_sensors( lss );
    }
}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int main(void)
{  
    /* SysTick end of count event each 10ms */
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);

    SystemInit();

    init_light_wheel();

    init_line_sensors();
    init_bumper();
    init_drive_motors();
    init_score_motors();

    FSM_STATE state = WALL_TO_CEN;
    SUP_SCO_ST sss = SCO_ST;

    drive_left_motor( STOPPED, NORMAL );
    drive_right_motor( STOPPED, NORMAL );
    drive_center_motor( STOPPED, NORMAL );

    //test_line_sensor( LS_FRONT );
    drive_score_motor_acmer( 930 );
    
    /**
        if( state ){
            set_score_motor_rot( 590 );
            state = 0;
        }else{
            set_score_motor_rot( 960 );
            state = 1;
        }
    **/

    // NEEDS ALIGN_TO_SUPPLY_PEGS
  
    while (1)
    {   
        update_light_wheel();

        switch( state ){
            case WALL_TO_CEN:
                if( wall_to_cen() == NEXT ){
                    if( sss == SCO_ST ){
                        state = ROT_LF_90;
                    }else{
                        // SUP_ST
                        state = ROT_RT_90;
                    }
                }
                break;

            case ROT_LF_90:
                if( rotate_left_90() == NEXT ){
                    state = CEN_TO_WALL;
                }
            break;

            case ROT_RT_90:
                if( rotate_right_90() == NEXT ){
                    state = CEN_TO_WALL;
                }
            break;

            case CEN_TO_WALL:
                if( cen_to_wall( sss ) == NEXT){
                    state = WALL_TO_CEN;

                    // Change Score and Supply States
                    if( sss == SCO_ST ){
                        sss = SUP_ST;
                    }else{
                        sss = SCO_ST;
                    }
                }
            break;

            default:
                state = WALL_TO_CEN;
                break;
        }
    }
}
