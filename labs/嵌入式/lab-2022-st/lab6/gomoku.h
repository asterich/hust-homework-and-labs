#ifndef GOMOKU_H
#define GOMOKU_H

#define BOARD_SIZE 12



typedef enum {
  NO_CHESS,
  BLACK_CHESS,
  WHITE_CHESS,
} player_t;

typedef player_t chess_t;


// -------------tool macros--------------------
#define OTHER(player) ((player == BLACK_CHESS) ? WHITE_CHESS : BLACK_CHESS)


// -------------game operations----------------

extern int game_over;
extern int game_started;
extern int curr_player;

// define error code for game operations
#define OK 0
#define ERR_GAME_OVER -1
#define ERR_GAME_NOT_STARTED -2
#define ERR_GAME_NOT_OVER -3
#define ERR_NOT_YOUR_TURN -4
#define ERR_BOARD -5

// initialize the game
void init_game();

// generate player randomly
int generate_player();

// place chess at game level
int place_chess(int x, int y, int player);

// restart game
int restart_game();

// exit the game
void exit_game();


// -------------board operations----------------

// define error code for board operations
#define OK 0
#define ERR_INVALID_POS -6
#define ERR_OCCUPIED -7

// initialize the board
void init_board();

// get the board, return a pointer to the board
void *get_board();

// put a chess on the board
int put_chess(int x, int y, chess_t chess);

// check if the player wins, 1 for win, 0 for not
int chk_win(player_t player);

// check if there has no space for putting chess
int chk_no_space();

#endif