#ifndef MOVEMENT_H_
#define MOVEMENT_H_

typedef enum{
   CONTINUE, NEXT
}STATE_TRANSITION;

STATE_TRANSITION rotate_right_90();
STATE_TRANSITION rotate_left_90();
STATE_TRANSITION follow_line_fw();
STATE_TRANSITION follow_line_rv();
STATE_TRANSITION wall_to_cen();
STATE_TRANSITION cen_to_wall();
STATE_TRANSITION to_past_line( LINE_SENSOR_T ls_t );
STATE_TRANSITION align_to_score_pegs();

#endif
