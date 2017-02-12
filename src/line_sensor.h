#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include "stm32f3_discovery.h"
#include "stm32f30x.h"

// Line Sensors
#define LS_PORT GPIOA
#define LS_PORT_CLOCK RCC_AHBPeriph_GPIOA

#define LS0 GPIO_Pin_0
#define LS1 GPIO_Pin_1
#define LS2 GPIO_Pin_2
#define LS3 GPIO_Pin_3
#define LS4 GPIO_Pin_4
#define LS5 GPIO_Pin_5
#define LS6 GPIO_Pin_6
#define LS7 GPIO_Pin_7

#define LS0_MASK 0x01
#define LS1_MASK 0x02
#define LS2_MASK 0x04
#define LS3_MASK 0x08
#define LS4_MASK 0x10
#define LS5_MASK 0x20
#define LS6_MASK 0x40
#define Ls7_MASK 0x80

void init_line_sensors();
uint16_t read_line_sensors();

#endif
