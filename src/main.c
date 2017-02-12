#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"

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

    GPIO_INIT_B( MOTOR_PIN_0 | MOTOR_PIN_1 | MOTOR_PIN_2 | MOTOR_PIN_3 );
    GPIO_INIT_E( MOTOR_PIN_0 );

    INIT_TIM1();
    EnableTimerInterrupt_TIM1();

    /* Initialize LEDs and User Button available on STM32F3-Discovery board */
    //STM_EVAL_LEDInit(LED3);


    //init_line_sensors();
    //setupOutputTimer();

  /* Infinite loop */
    int count;
    int dec;
    while (1)
    {   
        if( count == 5000 ){
            if( TIM1 -> CCR1 == 995 ){
                dec = 1;
            }else if( TIM1 -> CCR1 == 50){
                dec = 0;
            }

            TIM1 -> CCR1 = TIM1 -> CCR1 + (dec ? -1 : 1);
            count = 0;
        }

        count ++;
    }
}

