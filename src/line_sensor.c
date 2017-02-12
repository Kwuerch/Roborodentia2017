#include "line_sensor.h"

void init_line_sensors(){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd( LS_PORT_CLOCK, ENABLE );

    gpio.GPIO_Pin = ( LS0 | LS1 | LS2 | LS3 | LS4 | LS5 | LS6 | LS7 );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LS_PORT, &gpio);
}

uint16_t read_line_sensors(){
    return GPIO_ReadInputData(LS_PORT);
}
