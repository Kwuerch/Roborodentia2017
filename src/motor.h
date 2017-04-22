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
void drive_center_motor( MOTOR_SPEED_STATE mss, MOTOR_MOVEMENT_STATE mms );

void drive_score_motor_acmel(int rot);
void drive_score_motor_acmer(int rot);


void set_score_motor_rot(int pos);
void set_flag_motor_rot(int post);

#endif
