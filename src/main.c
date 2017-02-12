#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"
#include "light_wheel.h"

RCC_ClocksTypeDef RCC_Clocks;

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int main(void)
{  
    SystemInit();
    /* SysTick end of count event each 10ms */
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);

    init_light_wheel();

    GPIO_INIT( GPIOB,  MOTOR_PIN_0 | MOTOR_PIN_1 | MOTOR_PIN_2 | MOTOR_PIN_3 );

    INIT_TIM1();
    EnableTimerInterrupt_TIM1();

    //init_line_sensors();

  /* Infinite loop */
    while (1)
    {   
        update_light_wheel();
    }
}

