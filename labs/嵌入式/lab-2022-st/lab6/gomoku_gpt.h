#ifndef GOMOKU_GPT_H
#define GOMOKU_GPT_H

#include "gomoku.h"

#ifdef __cplusplus
extern "C" {
#endif

int get_comment_by_board(const int board[BOARD_SIZE][BOARD_SIZE], const int player, char *comment);

#ifdef __cplusplus
}
#endif


#endif