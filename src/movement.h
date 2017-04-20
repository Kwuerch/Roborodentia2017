#ifndef MOVEMENT_H_
#define MOVEMENT_H_

typedef enum{
   CONTINUE, NEXT
}STATE_TRANSITION;

typedef enum{
   SUP_ST, SCO_ST
}SUP_SCO_ST;

STATE_TRANSITION wall_to_cen();
STATE_TRANSITION cen_to_wall( SUP_SCO_ST sss );
STATE_TRANSITION to_past_line( LINE_SENSOR_T ls_t );
STATE_TRANSITION align_to_score_pegsr();


STATE_TRANSITION align_to_center_pegsl();
STATE_TRANSITION align_to_center_pegsl();

#endif
