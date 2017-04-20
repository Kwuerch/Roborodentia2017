#include "config.h"
#include "line_sensor.h"


#include "gpio.h"

void init_line_sensors(){
    GPIO_InitTypeDef gpio;

    RCC_AHBPeriphClockCmd( LS_PORT_CLOCK_F_B, ENABLE );
    RCC_AHBPeriphClockCmd( LS_PORT_CLOCK_SC_SP, ENABLE );

    gpio.GPIO_Pin = ( LS_FRONT_PINS | LS_BACK_PINS );
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( LS_PORT_F_B, &gpio);

    gpio.GPIO_Pin = ( LS_SCORE_PINS | LS_SUPPLY_PINS );
    GPIO_Init( LS_PORT_SC_SP, &gpio );
}

void test_line_sensors( LINE_SENSOR_T ls_t ){
    uint16_t sensor;
    if( ls_t == LS_FRONT ){
        sensor = ((LS_PORT_F_B -> IDR) >> 8) & 0xFF;
    }else if( ls_t == LS_BACK ){
        sensor = (LS_PORT_F_B -> IDR) & 0xFF;
    }else if( ls_t == LS_SCORE || ls_t == LS_SUPPLY ){
        sensor = (LS_PORT_SC_SP -> IDR) & 0x0F;
    }else{
        sensor = 0;
    }

    GPIOE -> ODR = sensor << 8;
}

SENSOR_LOC line_loc( LINE_SENSOR_T ls_t ){
    uint16_t sensor;
    if( ls_t == LS_FRONT ){
        sensor = ((LS_PORT_F_B -> IDR) >> 8) & 0xFF;
    }else if( ls_t == LS_BACK ){
        sensor = (LS_PORT_F_B -> IDR) & 0xFF;
    }else{
        sensor = 0;
    }
  
    if( sensor == FULL_MASK ){
        return FULL;
    }else if( sensor & LEFT_MASK ){
        return LEFT;
    }else if( sensor & RIGHT_MASK ){
        return RIGHT;
    }else if( sensor & CENTER_MASK ){
        return CENTER;
    }else{
        return EMPTY;
    }
}

// For Sensor Array with only 2 lights -> LS_SCORE & LS_SUPPLY
SENSOR_LOC line_loc2( LINE_SENSOR_T ls_t ){
    uint16_t sensor;
    if( ls_t == LS_SCORE ){
        sensor = (LS_PORT_SC_SP -> IDR) & 0x03;
    }else if( ls_t == LS_SUPPLY ){
        sensor = ((LS_PORT_SC_SP -> IDR) >> 2) & 0x03;
    }else{
        sensor = 0;
    }

    if( sensor == FULL_MASK2 ){
        return FULL;
    }else if( sensor & RIGHT_MASK2 ){
        return RIGHT;
    }else if( sensor & LEFT_MASK2 ){
        return LEFT;
    }else{
        return EMPTY;
    }
}
