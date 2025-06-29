#ifndef  GOMOKU_AI_H_
#define  GOMOKU_AI_H_

#include "gomoku.h"

void set_ai_player(int player);
int get_ai_player();
int ai_begin();
int ai_turn(const int board[BOARD_SIZE][BOARD_SIZE]);

#endif   //_FIVECHESS_h_
