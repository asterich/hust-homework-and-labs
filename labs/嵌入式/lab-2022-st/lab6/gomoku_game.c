#include "gomoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game_started;
int game_over;
int curr_player;

void init_game() {
  init_board();
  game_started = 0;
  game_over = 0;
  curr_player = BLACK_CHESS;
  return;
}

int generate_player() {
  srand(time(NULL));
  int generated_player = (rand() % 2) + 1;
  printf("generated player: %d\n", generated_player);
  return generated_player;
}

int place_chess(int x, int y, int player) {
    if (game_over)
        return ERR_GAME_OVER;
    if (game_started == 0)
        return ERR_GAME_NOT_STARTED;
    if (player != curr_player)
        return ERR_NOT_YOUR_TURN;
    int ret = put_chess(x, y, curr_player);
    if (ret == OK) {
        if (chk_win(curr_player)) {
            game_over = 1;
            return OK;
        }
        curr_player = (curr_player == BLACK_CHESS) ? WHITE_CHESS : BLACK_CHESS;
    }
    return ret;
}

int restart_game() {
    if (game_over == 0)
        return ERR_GAME_NOT_OVER;
    init_game();
    printf("curr_player %d\n", curr_player);
    game_over = 0;
    game_started = 1;
    return OK;
}

void exit_game() {
    game_started = 0;
    game_over = 0;
    curr_player = BLACK_CHESS;
    return;
}

