#include "config.h"
#include "line_sensor.h"


#include "gpio.h"

void init_line_sensors(){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd( LS_PORT_CLOCK, ENABLE );

    gpio.GPIO_Pin = ( LS_FRONT_PINS | LS_BACK_PINS );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LS_PORT_F, &gpio);
}

void test_line_sensors( LINE_SENSOR_T ls_t ){
    uint16_t sensor;
    if( ls_t == LS_FRONT ){
        sensor = ((LS_PORT_F -> IDR) >> 8) & 0xFF;
    }else if( ls_t == LS_BACK ){
        sensor = (LS_PORT_B -> IDR) & 0xFF;
    }else{
        sensor = ((LS_PORT_F -> IDR) >> 8) & 0xFF;
    }

    GPIOE -> ODR = sensor << 8;
}

SENSOR_LOC line_loc( LINE_SENSOR_T ls_t ){
    uint16_t sensor;
    if( ls_t == LS_FRONT ){
        sensor = ((LS_PORT_F -> IDR) >> 8) & 0xFF;
    }else if( ls_t == LS_BACK ){
        sensor = (LS_PORT_B -> IDR) & 0xFF;
    }else{
        sensor = ((LS_PORT_F -> IDR) >> 8) & 0xFF;
    }

  
    if( sensor == FULL_MASK ){
        return FULL;
    }else if( sensor & CENTER_MASK ){
        return CENTER;
    }else if( sensor & LEFT_MASK ){
        return LEFT;
    }else if( sensor & RIGHT_MASK ){
        return RIGHT;
    }else{
        return EMPTY;
    }
}
