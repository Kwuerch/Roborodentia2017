#ifndef MOTOR_H_
#define MOTOR_H_

void init_drive_motors();
void init_score_motors();
void drive_left_motor(int8_t speed);
void drive_right_motor(int8_t speed);
void drive_center_motor(int8_t speed);
void drive_score_motor_1(int rot);
void drive_score_motor_2(int rot);

#endif
