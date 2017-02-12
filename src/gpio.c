#include "stm32f3_discovery.h"
#include "stm32f30x.h"

void GPIO_INIT( GPIO_TypeDef* GPIOx, uint16_t pin ){
    if( GPIOx == GPIOA ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    }else if( GPIOx == GPIOB ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    }else if( GPIOx == GPIOC ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    }else if( GPIOx == GPIOD ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    }else if( GPIOx == GPIOE ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    }else if( GPIOx == GPIOF ){
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
    }

    GPIO_InitTypeDef GPIO_InitTypeDef;

    GPIO_InitTypeDef.GPIO_Pin = pin;
    GPIO_InitTypeDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitTypeDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init( GPIOx, &GPIO_InitTypeDef );
}

void setPin(GPIO_TypeDef* GPIOx, uint16_t pin){
    GPIOx -> BSRR |= pin; 
}

void resetPin(GPIO_TypeDef* GPIOx, uint16_t pin){
    GPIOx -> BRR |= pin;
}

void togglePin(GPIO_TypeDef* GPIOx, uint16_t pin){
    uint16_t tog = (GPIOx -> ODR) ^ pin;

    uint32_t bsrr_new = ~tog;
    bsrr_new <<= 16;
    bsrr_new |= tog;

    GPIOx -> BSRR = bsrr_new;
}

void setLedsFromInput( uint16_t input ){
    GPIOE -> BSRR = input << 8;
    GPIOE -> BRR = (~input) << 8;
}
