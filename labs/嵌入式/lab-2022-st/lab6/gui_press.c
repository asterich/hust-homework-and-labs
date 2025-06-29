#include <linux/fb.h>
#include <stdio.h>
#include <sys/mman.h>

#include "../common/common.h"

#include "board_interact.h"
#include "button.h"
#include "gomoku.h"
#include "gomoku_draw.h"

static int touch_fd;
static struct old_pos {
  int x;
  int y;
} old[5];

static int player = BLACK_CHESS;

static void touch_event_cb(int fd) {
  int type, x, y, finger, color;
  type = touch_read(fd, &x, &y, &finger);
  switch (type) {
  case TOUCH_PRESS: {
    printf("TOUCH_PRESS:x=%d,y=%d,finger=%d\n", x, y, finger);
    button_t *btn = press_button(x, y);
    if (btn != NULL) {
      old[0].x = x;
      old[0].y = y;
      break;
    }
    unsigned int board_pos = calc_chess_position(x, y);
    printf("board_pos=%x\n", board_pos);
    if (board_pos != (unsigned int)-1) {
      int chess_x = board_pos >> 16;
      int chess_y = board_pos & 0xffff;
      printf("chess_x=%d, chess_y=%d\n", chess_x, chess_y);
      int err_place = place_chess(chess_x, chess_y, player);
      if (err_place == OK) {
        draw_chess(chess_x, chess_y, player);

        if (chk_win(player)) {
          printf("player %d win\n", player);
          game_over = 1;
        } else {
          player = (player == BLACK_CHESS) ? WHITE_CHESS : BLACK_CHESS;
        }
      } else {
        printf("place_chess error: %d\n", err_place);
      }
    }
  } break;
  case TOUCH_MOVE:
    printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n", x, y, finger);
    break;
  case TOUCH_RELEASE: {
    printf("TOUCH_RELEASE:x=%d,y=%d,finger=%d\n", x, y, finger);
    button_t *btn = release_button(old[0].x, old[0].y);
    if (btn != NULL) {
      if (btn->text[0] == 'S') {
        printf("start button released\n");
      } else if (btn->text[0] == 'R') {
        printf("restart button released\n");
        int err_restart = restart_game();
        if (err_restart == OK) {
          printf("restart game\n");
          player = BLACK_CHESS;
          printf("player %d, curr_player %d\n", player, curr_player);
          draw_board();
          display_buttons();
        } else {
          printf("restart game error: %d\n", err_restart);
        }
      }
    }
    old[0].x = 0;
    old[0].y = 0;
  } break;
  case TOUCH_ERROR:
    printf("close touch fd\n");
    close(fd);
    task_delete_file(fd);
    break;
  default:
    return;
  }
  display_buttons();
  update();
  return;
}

int main(int argc, char *argv[]) {
  fb_init("/dev/fb0");
  font_init("./font.ttc");

  fb_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
  draw_board();
  update();

  register_button(START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH,
                  START_BUTTON_HEIGHT, YELLOW, BLACK,
                  "Start"); //注册开始按钮
  register_button(RESTART_BUTTON_X, RESTART_BUTTON_Y, RESTART_BUTTON_WIDTH,
                  RESTART_BUTTON_HEIGHT, YELLOW, BLACK,
                  "Restart"); //注册退出按钮
  display_buttons();
  update();

  init_game();
  game_started = 1;

  // 打开多点触摸设备文件, 返回文件fd
  touch_fd = touch_init("/dev/input/event2");
  // 添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
  task_add_file(touch_fd, touch_event_cb);

  task_loop(); // 进入任务循环
  return 0;
}