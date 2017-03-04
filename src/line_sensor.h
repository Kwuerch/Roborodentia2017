#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

typedef enum{
   LEFT, CENTER, RIGHT
}SENSOR_LOC;

SENSOR_LOC line_loc();
void init_line_sensors();
void update_line_sensors();

#endif
