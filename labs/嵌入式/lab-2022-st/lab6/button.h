#ifndef BUTTON_H
#define BUTTON_H

#include "../common/common.h"
#include <stdio.h>

#include "gomoku_draw.h"

#define BOARD_NUM 12

#define MAX_BUTTON_NUM 10

typedef struct {
  int x;
  int y;
  int w;
  int h;
  int bgcolor;
  int fontcolor;
  int pressed;
  char text[100];
} button_t;

// init button module
void init_button();

// register button
int register_button(int x, int y, int w, int h, int bgcolor, int fontcolor, char *text);

// determine which button user pressed, return null if nothing pressed
button_t *press_button(int x, int y);

// determine which button user released, return null if nothing released
button_t *release_button(int x, int y);

// display all buttons
void display_buttons();

#endif