#include "gomoku.h"
#include <stdio.h>

static int board[BOARD_SIZE][BOARD_SIZE];
static int chess_cnt;

void init_board() {
  chess_cnt = 0;
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = NO_CHESS;
}

void *get_board() { return (void *)board; }

int put_chess(int x, int y, chess_t chess) {
  if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
    return ERR_INVALID_POS;
  if (board[x][y] != NO_CHESS)
    return ERR_OCCUPIED;
  board[x][y] = chess;
  chess_cnt++;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++)
      printf("%d ", board[j][i]);
    printf("\n");
  }

  return OK;
}

int chk_win(player_t player) {
  int i, j, k, l;
  int cnt;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] != player)
        continue;
      for (k = -1; k <= 1; k++)
        for (l = -1; l <= 1; l++) {
          if (k == 0 && l == 0)
            continue;
          cnt = 1;
          while (1) {
            int x = i + cnt * k;
            int y = j + cnt * l;
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
              break;
            if (board[x][y] != player)
              break;
            cnt++;
          }
          if (cnt >= 5)
            return 1;
        }
    }
  return 0;
}

int chk_no_space() { return chess_cnt == BOARD_SIZE * BOARD_SIZE; }