#ifndef BOARD_INTERACT_H
#define BOARD_INTERACT_H

#include "../common/common.h"
#include "gomoku_draw.h"

// calculate the chess position from the gui position
// returns the packed chess position, high 16 bits for x, low 16 bits for y
// returns 0xFFFFFFFF if invalid
unsigned int calc_chess_position(int gui_x, int gui_y);


#endif