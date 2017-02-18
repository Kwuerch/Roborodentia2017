#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"
#include "light_wheel.h"
#include "motor.h"

RCC_ClocksTypeDef RCC_Clocks;

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

    //init_line_sensors();
    init_drive_motors();
    init_score_motors();

    drive_right_motor(25);
    drive_center_motor(75);
    drive_left_motor(-60);
    // drive_score_motor_1(24);
    //Delay(10000);
    //drive_score_motor_1(-24);


  /* Infinite loop */
    while (1)
    {   
        update_light_wheel();

        //drive_score_motor_1(500);
        //Delay(100);
        //drive_score_motor_1(500);
    }
}

