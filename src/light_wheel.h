#ifndef LIGHT_WHEEL_H
#define LIGHT_WHEEL_H

#define LED3 GPIO_Pin_9
#define LED4 GPIO_Pin_8
#define LED5 GPIO_Pin_10
#define LED6 GPIO_Pin_15
#define LED7 GPIO_Pin_11
#define LED8 GPIO_Pin_14
#define LED9 GPIO_Pin_12
#define LED10 GPIO_Pin_13

#define LED_PINS LED3 | LED4 | LED5 | LED6 | LED7 | LED8 | LED9 | LED10 

#define LED_PORT GPIOE

#define NUM_LEDS 8

void init_light_wheel();
void update_light_wheel();

#endif
