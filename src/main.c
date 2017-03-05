#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"
#include "light_wheel.h"
#include "motor.h"
#include "movement.h"
#include "i2c.h"

RCC_ClocksTypeDef RCC_Clocks;

extern uint8_t sensor_c;
extern uint16_t sensor_lr;

typedef enum{
    START, REVERSE_TURN, GET_RINGS, TO_FLAG, TO_CENTER, TO_SCORE, DROP_RINGS, SET_FLAG, FOLLOW_LINE, STOP
}FSM_STATE;

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
    init_drive_motors();
    init_score_motors();

    FSM_STATE state = FOLLOW_LINE;

  /* Infinite loop */
    while (1)
    {   
        //update_line_sensors();
        update_light_wheel();
        //follow_line_rv();

        switch( state ){
            case STOP:
                state = STOP;
                break;
                
            case FOLLOW_LINE:
                if( follow_line_fw() == NEXT ){
                    drive_left_motor( STOPPED, NORMAL );
                    drive_right_motor( STOPPED, NORMAL );
                    state = STOP;
                }
                break;
            default:
                state = FOLLOW_LINE;
                break;
        }
                
            /** case START:
                state = GET_RINGS;
                break;

            case REVERSE_TURN:
                if( reverse_turn_fsm() == NEXT_STATE ){
                    state = TO_CENTER;
                }
                break;



            case GET_RINGS:
            case TO_FLAG:
            case TO_CENTER:
            case TO_SCORE:
            case DROP_RINGS:
            case SET_FLAG:

            default:
                state = START;
                break;
        }
        **/
    }
}
