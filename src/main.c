#include "stm32f3_discovery.h"
#include "stm32f30x.h"

/* Private variables ---------------------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;
uint32_t counter = 0;
uint16_t light_wheel[] = {LED3, LED4, LED6, LED8, LED10, LED9, LED7, LED5};

/* Private function prototypes -----------------------------------------------*/
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/
void TM_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TM_TIMER_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_BaseStruct.TIM_Prescaler = 0;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_BaseStruct.TIM_Period = 8399; // 10 khz pwm
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;

    //Initialize Tim 4
    TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);

    // Start Count on TIM4
    TIM_Cmd(TIM4, ENABLE);
}

void TM_PWM_Init(void) {
    TIM_OCInitTypeDef TIM_OCStruct;

    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OCStruct.TIM_Pulse = 2099; // 25%
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);


    TIM_OCStruct.TIM_Pulse = 4199; /** 50 % duty cycle */
    TIM_OC2Init(TIM4, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = 6299; // 75%
    TIM_OC3Init(TIM4, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = 8399; // 100% duty cycle
    TIM_OC4Init(TIM4, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int main(void)
{  

    SystemInit();
  /* SysTick end of count event each 10ms */
  //RCC_GetClocksFreq(&RCC_Clocks);
  //SysTick_Config(RCC_Clocks.HCLK_Frequency / 10);

   
  /* Initialize LEDs and User Button available on STM32F3-Discovery board */
  //STM_EVAL_LEDInit(LED3);

  TM_GPIO_Init();
  TM_TIMER_Init();
  TM_PWM_Init();


  /* Infinite loop */
  while (1)
  {   
  }
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
