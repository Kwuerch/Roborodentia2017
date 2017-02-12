#include "stm32f3_discovery.h"
#include "stm32f30x.h"

uint16_t light_wheel[] = {LED3, LED4, LED6, LED8, LED10, LED9, LED7, LED5};

void GPIO_INIT_A(uint16_t pin){
    GPIO_InitTypeDef gpio; RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    gpio.GPIO_Pin = pin;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &gpio);
}

void GPIO_INIT_B(uint16_t pin){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    gpio.GPIO_Pin = pin;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &gpio);
}

void GPIO_INIT_E(uint16_t pin){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

    gpio.GPIO_Pin = pin;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOE, &gpio);
}

void setPin(GPIO_TypeDef* gpio_port , uint16_t pin){
    gpio_port -> BSRR |= pin; 
}

void resetPin(GPIO_TypeDef* gpio_port, uint16_t pin){
    gpio_port -> BRR |= pin;
}

void togglePin(GPIO_TypeDef* gpio_port, uint16_t pin){
    uint16_t tog = (gpio_port -> ODR) ^ pin;

    uint32_t bsrr_new = ~tog;
    bsrr_new <<= 16;
    bsrr_new |= tog;

    gpio_port -> BSRR = bsrr_new;
}

void setLedsFromInput( uint16_t input ){
    GPIOE -> BSRR = input << 8;
    GPIOE -> BRR = (~input) << 8;
}
