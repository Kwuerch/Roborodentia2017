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

void game_fsm(){
    while( 1 ){
        update_light_wheel();

    }
}

int test_line_sensor_inf( LINE_SENSOR_T lss){
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
    uint8_t from_sup = 1;

    drive_left_motor( STOPPED, NORMAL );
    drive_right_motor( STOPPED, NORMAL );
    drive_center_motor( STOPPED, NORMAL );

    test_line_sensor_inf( LS_SUPPLY );

    while (1)
    {   
        update_light_wheel();

        switch( state ){
            case WALL_TO_CEN:
                if( wall_to_cen() == NEXT ){
                    if( from_sup ){
                        from_sup = 0;
                        state = ROT_LF_90;    
                    }else{
                        from_sup = 1;
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
                if( cen_to_wall() == NEXT){
                    state = WALL_TO_CEN;
                }
            break;

            default:
                state = WALL_TO_CEN;
                break;
        }
    }
}
