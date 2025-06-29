#include "board_interact.h"

unsigned int calc_chess_position(int gui_x, int gui_y) {
    int chess_x = (gui_x - BOARD_X) / OUTER_GRID_SIZE;
    int chess_y = (gui_y - BOARD_Y) / OUTER_GRID_SIZE;
    return (chess_x << 16) | chess_y;
}
