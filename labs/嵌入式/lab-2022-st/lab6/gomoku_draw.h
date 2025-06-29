#ifndef GOMOKU_DRAW_H
#define GOMOKU_DRAW_H

#include "../common/common.h"
#include <stdio.h>

#include "gomoku.h"

// sizes of widgets
#define BOARD_NUM 12

#define OUTER_GRID_SIZE 40
#define CHESS_SIZE 30

#define BOARD_X 30
#define BOARD_Y 30

#define START_BUTTON_WIDTH 150
#define START_BUTTON_HEIGHT 60
#define START_BUTTON_X 558
#define START_BUTTON_Y 150


#define RESTART_BUTTON_WIDTH 150
#define RESTART_BUTTON_HEIGHT 60
#define RESTART_BUTTON_X 558
#define RESTART_BUTTON_Y 250

#define TEXT_TITLE_X 640
#define TEXT_TITLE_Y 80

#define TEXT_GPT_MSG_X 558
#define TEXT_GPT_MSG_Y 350
#define TEXT_GPT_MSG_WIDTH 400
#define TEXT_GPT_MSG_HEIGHT 120

#define TEXT_ERR_MSG_X 558
#define TEXT_ERR_MSG_Y 500
#define TEXT_ERR_MSG_WIDTH 400
#define TEXT_ERR_MSG_HEIGHT 60

#define TEXT_PLAYER_X 790
#define TEXT_PLAYER_Y 200
#define TEXT_PLAYER_WIDTH 200
#define TEXT_PLAYER_HEIGHT 60

// text content
#define TEXT_TITLE "妹系AI五子棋"
#define TEXT_PLAYER_FMT "玩家：%s"

// font size
#define FONT_SIZE_TITLE 30
#define FONT_SIZE_BUTTON 20
#define FONT_SIZE_INFO_MSG 24
#define FONT_SIZE_ERR_MSG 20
#define FONT_SIZE_GPT_MSG 20


// color
#define RED FB_COLOR(255, 0, 0)
#define ORANGE FB_COLOR(255, 165, 0)
#define YELLOW FB_COLOR(255, 255, 0)
#define GREEN FB_COLOR(0, 255, 0)
#define CYAN FB_COLOR(0, 127, 255)
#define BLUE FB_COLOR(0, 0, 255)
#define PURPLE FB_COLOR(139, 0, 255)
#define WHITE FB_COLOR(255, 255, 255)
#define BLACK FB_COLOR(0, 0, 0)

#define COLOR_BACKGROUND WHITE
#define COLOR_GRID BLACK


void draw_board();
void draw_chess(int chess_x, int chess_y, chess_t chess);
void draw_button(int x, int y, int width, int height, int bgcolor, int fontcolor, char *text);
void draw_button_pressed(int x, int y, int width, int height, int bgcolor, int fontcolor, char *text);
void draw_text(int x, int y, int width, int height, int font_size, int color, char *text);
void draw_multiline_text(int x, int y, int width, int height, int font_size, int color, char c_text[]);
void clear_bg(int x, int y, int width, int height);
void update();


#endif