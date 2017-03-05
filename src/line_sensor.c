#include "config.h"
#include "line_sensor.h"


#include "gpio.h"

uint8_t sensor_c;
uint16_t sensor_lr;

void init_line_sensors(){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd( LS_PORT_CLOCK, ENABLE );

    gpio.GPIO_Pin = ( LS_CENTER_PINS );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LS_PORT_C, &gpio);

    //RCC_AHBPeriphClockCmd( LS_PORT_CLOCK, ENABLE );

    /**
    gpio.GPIO_Pin = ( LS0 | LS1 | LS2 | LS3 | LS4 | LS5 | LS6 | LS7 |
            LS8 | LS9 | LS10 | LS11 | LS12 | LS13 | LS14 | LS15 );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LS_PORT_LR, &gpio);
    **/
}

void update_line_sensors(){
    sensor_c = ((LS_PORT_C -> IDR) >> 8) & 0xFF;
    /**
    if( line_loc() == CENTER ){
        GPIOE -> ODR = 0x0000;
        uint16_t test = sensor_c << 8;
        GPIOE -> ODR = test;
    }else if( line_loc() == RIGHT ){
        GPIOE -> ODR  = 0x0F00;
    }else{
        GPIOE -> ODR = 0xF000;
    }
    **/
    //sensor_lr = (LS_PORT_LR -> IDR) & 0xFFFF;
}

SENSOR_LOC line_loc(){
    sensor_c = ((LS_PORT_C -> IDR) >> 8) & 0xFF;
  
    if( sensor_c == FULL_MASK ){
        return FULL;
    }else if( sensor_c & CENTER_MASK ){
        return CENTER;
    }else if( sensor_c & LEFT_MASK ){
        return LEFT;
    }else if( sensor_c & RIGHT_MASK ){
        return RIGHT;
    }else{
        return CENTER;
    }
    
}
