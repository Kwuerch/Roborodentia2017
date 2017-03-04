#ifndef MOVEMENT_H_
#define MOVEMENT_H_

typedef enum{
   CONTINUE, NEXT
}STATE_TRANSITION;

STATE_TRANSITION reverse_turn();
STATE_TRANSITION follow_line_fw();
STATE_TRANSITION follow_line_rv();

#endif
