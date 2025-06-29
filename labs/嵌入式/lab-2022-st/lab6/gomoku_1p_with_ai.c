#include <linux/fb.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#include "../common/common.h"

#include "board_interact.h"
#include "button.h"
#include "gomoku.h"
#include "gomoku_ai.h"
#include "gomoku_draw.h"
#include "gomoku_err.h"
#include "gomoku_gpt.h"

static int touch_fd;
static struct old_pos {
  int x;
  int y;
} old[5];

static int player = BLACK_CHESS;

static char gpt_comment[512];

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
        update();

        if (chk_win(player)) {
          printf("player %d win\n", player);
          game_over = 1;

          // print winner info at where player info displays
          clear_bg(TEXT_PLAYER_X, TEXT_PLAYER_Y - 30, TEXT_PLAYER_WIDTH,
                   TEXT_PLAYER_HEIGHT);
          draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                    TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK,
                    "哥哥你赢啦！");
        } else if (chk_no_space()) {
          printf("tie!\n");
          game_over = 1;
          clear_bg(TEXT_PLAYER_X, TEXT_PLAYER_Y - 30, TEXT_PLAYER_WIDTH,
                   TEXT_PLAYER_HEIGHT);
          draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                    TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK, "平局");
        }

        // gpt comment
        int comment_length =
            get_comment_by_board(get_board(), player, gpt_comment);
        if (comment_length > 0) {
          printf("gpt comment: %s\n", gpt_comment);
          clear_bg(TEXT_GPT_MSG_X, TEXT_GPT_MSG_Y - 30,
                   TEXT_GPT_MSG_WIDTH + FONT_SIZE_GPT_MSG * 2,
                   TEXT_GPT_MSG_HEIGHT);
          draw_multiline_text(TEXT_GPT_MSG_X, TEXT_GPT_MSG_Y,
                              TEXT_GPT_MSG_WIDTH, TEXT_GPT_MSG_HEIGHT,
                              FONT_SIZE_GPT_MSG, BLACK, gpt_comment);
          update();
        }

        // sleep for 0.5s
        nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);

        // then it's ai's turn
        if (game_over == 0) {
          int zipped_pos = ai_turn((int(*)[12])get_board());
          int chess_x = (zipped_pos >> 16) & 0xffff,
              chess_y = zipped_pos & 0xffff;
          place_chess(chess_x, chess_y, get_ai_player());
          draw_chess(chess_x, chess_y, get_ai_player());

          if (chk_win(get_ai_player())) {
            printf("player %d win\n", get_ai_player());
            game_over = 1;

            // print winner info at where player info displays
            clear_bg(TEXT_PLAYER_X, TEXT_PLAYER_Y - 30, TEXT_PLAYER_WIDTH,
                     TEXT_PLAYER_HEIGHT);
            draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                      TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK,
                      "哥哥你输了呜呜");
          } else if (chk_no_space()) {
            printf("tie!\n");
            game_over = 1;
            clear_bg(TEXT_PLAYER_X, TEXT_PLAYER_Y - 30, TEXT_PLAYER_WIDTH,
                     TEXT_PLAYER_HEIGHT);
            draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                      TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK, "平局");
          }
        }
      } else {
        printf("place_chess error: %d\n", err_place);
        clear_bg(TEXT_ERR_MSG_X, TEXT_ERR_MSG_Y - 50, TEXT_ERR_MSG_WIDTH,
                 TEXT_ERR_MSG_HEIGHT);
        draw_text(TEXT_ERR_MSG_X, TEXT_ERR_MSG_Y, TEXT_ERR_MSG_WIDTH,
                  TEXT_ERR_MSG_HEIGHT, FONT_SIZE_ERR_MSG, RED,
                  get_err_msg(err_place));
        update();
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
        // do stuffs for start
        init_game();
        game_started = 1;

        // generate player
        player = generate_player();
        set_ai_player(OTHER(player));
        printf("player: %d, ai_player: %d\n", player, get_ai_player());

        char player_str[64];
        snprintf(player_str, 63, TEXT_PLAYER_FMT,
                 player == BLACK_CHESS ? "黑方" : "白方");
        draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                  TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK, player_str);

        // ai should put chess if it is black's turn
        if (get_ai_player() == BLACK_CHESS) {
          int zipped_pos = ai_begin();
          int chess_x = (zipped_pos >> 16) & 0xffff,
              chess_y = zipped_pos & 0xffff;
          place_chess(chess_x, chess_y, get_ai_player());
          draw_chess(chess_x, chess_y, get_ai_player());
        }

      } else if (btn->text[0] == 'R') {
        printf("restart button released\n");
        int err_restart = restart_game();
        if (err_restart == OK) {
          printf("restart game\n");

          // do stuffs for restart
          draw_board();
          display_buttons();

          // set player
          player = generate_player();
          set_ai_player(OTHER(player));
          printf("player: %d, ai_player: %d\n", player, get_ai_player());

          // ai should put chess if it is black's turn
          if (get_ai_player() == BLACK_CHESS) {
            int zipped_pos = ai_begin();
            int chess_x = (zipped_pos >> 16) & 0xffff,
                chess_y = zipped_pos & 0xffff;
            place_chess(chess_x, chess_y, get_ai_player());
            draw_chess(chess_x, chess_y, get_ai_player());
          }

          printf("player %d, curr_player %d\n", player, curr_player);
          clear_bg(TEXT_ERR_MSG_X, TEXT_ERR_MSG_Y - 30, TEXT_ERR_MSG_WIDTH,
                   TEXT_ERR_MSG_HEIGHT);
          clear_bg(TEXT_GPT_MSG_X, TEXT_GPT_MSG_Y - 30,
                   TEXT_GPT_MSG_WIDTH + FONT_SIZE_GPT_MSG * 2,
                   TEXT_GPT_MSG_HEIGHT);

          // draw player info text
          clear_bg(TEXT_PLAYER_X, TEXT_PLAYER_Y - 30, TEXT_PLAYER_WIDTH,
                   TEXT_PLAYER_HEIGHT);
          char player_str[64];
          snprintf(player_str, 63, TEXT_PLAYER_FMT,
                   player == BLACK_CHESS ? "黑方" : "白方");
          draw_text(TEXT_PLAYER_X, TEXT_PLAYER_Y, TEXT_PLAYER_WIDTH,
                    TEXT_PLAYER_HEIGHT, FONT_SIZE_INFO_MSG, BLACK, player_str);
        } else {
          printf("restart game error: %d\n", err_restart);
          clear_bg(TEXT_ERR_MSG_X, TEXT_ERR_MSG_Y - 30, TEXT_ERR_MSG_WIDTH,
                   TEXT_ERR_MSG_HEIGHT);
          draw_text(TEXT_ERR_MSG_X, TEXT_ERR_MSG_Y, TEXT_ERR_MSG_WIDTH,
                    TEXT_ERR_MSG_HEIGHT, FONT_SIZE_ERR_MSG, RED,
                    get_err_msg(err_restart));
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
  draw_text(TEXT_TITLE_X, TEXT_TITLE_Y, 0, 0, 40, BLACK, TEXT_TITLE);
  update();

  register_button(START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH,
                  START_BUTTON_HEIGHT, YELLOW, BLACK,
                  "Start"); //注册开始按钮
  register_button(RESTART_BUTTON_X, RESTART_BUTTON_Y, RESTART_BUTTON_WIDTH,
                  RESTART_BUTTON_HEIGHT, YELLOW, BLACK,
                  "Restart"); //注册退出按钮
  display_buttons();
  update();

  // 打开多点触摸设备文件, 返回文件fd
  touch_fd = touch_init("/dev/input/event1");
  // 添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
  task_add_file(touch_fd, touch_event_cb);

  task_loop(); // 进入任务循环
  return 0;
}