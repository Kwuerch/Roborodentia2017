#include "config.h"

void init_bumper(){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd( BUMPER_PORT_CLOCK, ENABLE );

    gpio.GPIO_Pin = ( BUMPER_PINS );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( BUMPER_PORT, &gpio);
}

int front_bumper_dep(){
    return (((BUMPER_PORT -> IDR) & BUMPER_FRONT) == BUMPER_FRONT);
}

int back_bumper_dep(){
    return (((BUMPER_PORT -> IDR) & BUMPER_BACK) == BUMPER_BACK);
}
