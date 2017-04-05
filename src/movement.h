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

#endif
