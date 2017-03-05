#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum{
   FAST_FW, FAST_RV, SLOW_FW, SLOW_RV, STOPPED
}MOTOR_SPEED_STATE;

typedef enum{
   NORMAL, PIVOT, MOVING
}MOTOR_MOVEMENT_STATE;

void init_drive_motors();
void init_score_motors();

void drive_left_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms );
void drive_right_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms );
void drive_center_motor(int8_t speed);

void drive_score_motor_1(int rot);
void drive_score_motor_2(int rot);

#endif
