#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

typedef enum{
   LEFT, CENTER, RIGHT, FULL, EMPTY
}SENSOR_LOC;

typedef enum{
   LS_FRONT, LS_BACK, LS_SCORE, LS_SUPPLY
}LINE_SENSOR_T;

SENSOR_LOC line_loc( LINE_SENSOR_T );
SENSOR_LOC line_loc2( LINE_SENSOR_T );
void test_line_sensors( LINE_SENSOR_T );
void init_line_sensors();

#endif
