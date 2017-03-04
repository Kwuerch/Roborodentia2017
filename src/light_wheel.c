#include "light_wheel.h"
#include "gpio.h"
#include "config.h"

uint16_t LEDS[] = {LED3, LED5, LED7, LED9, LED10, LED8, LED6, LED4 };

void init_light_wheel(){
    GPIO_INIT( GPIOE, LED_PINS );
}

void update_light_wheel(){
    static int indx = 0;
    static int cnt = 0;

    if( cnt == 200000 ){
        cnt = 0;
        resetPin( LED_PORT, LEDS[indx++] );

        if( indx == NUM_LEDS ){
            indx = 0;
        }

        setPin( LED_PORT, LEDS[indx] );
    }

    cnt++;
}
