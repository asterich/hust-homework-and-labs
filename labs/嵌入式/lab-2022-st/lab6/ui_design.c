#include <linux/fb.h>
#include <stdio.h>
#include <sys/mman.h>

#include "../common/common.h"

#include "gomoku_draw.h"

int color[9] = {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, BLACK};

int main(int argc, char *argv[]) {

  fb_init("/dev/fb0");
  font_init("./font.ttc");

  fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
  draw_board();
  draw_chess(0, 0, BLACK_CHESS);
  draw_chess(1, 11, BLACK_CHESS);
  draw_chess(5, 5, WHITE_CHESS);
  draw_chess(11, 1, WHITE_CHESS);
  draw_button(START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH,
              START_BUTTON_HEIGHT, YELLOW, BLACK, "START");
  update();

  return 0;
}