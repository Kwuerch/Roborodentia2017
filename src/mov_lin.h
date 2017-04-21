#ifndef MOV_LIN_H_
#define MOV_LIN_H_

#include "movement.h"

STATE_TRANSITION fw_slow();

STATE_TRANSITION follow_line_fw();
STATE_TRANSITION follow_line_rv();

#endif
