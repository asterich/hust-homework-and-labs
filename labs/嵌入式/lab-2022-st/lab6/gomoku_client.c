#include <linux/fb.h>
#include <stdio.h>
#include <sys/mman.h>

#include "../common/common.h"

#include "board_interact.h"
#include "button.h"
#include "gomoku_draw.h"

static int touch_fd;
static int bluetooth_fd1;
static int bluetooth_fd2;
static int t_snd[128];

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
      printf("client put chess at: chess_x=%d, chess_y=%d, player=%d\n", chess_x, chess_y, player);

      // send pos message to server
      t_snd[0] = 2;
      t_snd[1] = (chess_x << 16) | chess_y;
      t_snd[2] = player;
      myWrite_nonblock(bluetooth_fd2, t_snd, 3 * sizeof(int));
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
        // send start message to server
        t_snd[0] = 0;
        myWrite_nonblock(bluetooth_fd2, t_snd, 1 * sizeof(int));
      } else if (btn->text[0] == 'R') {
        printf("restart button released\n");
        // do things for restarting

        // send restart message to server
        t_snd[0] = 1;
        myWrite_nonblock(bluetooth_fd2, t_snd, 1 * sizeof(int));
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

static int bluetooth_tty_init(const char *dev) {
  int fd = open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK); /*非阻塞模式*/
  if (fd < 0) {
    printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno,
           strerror(errno));
    return -1;
  }
  return fd;
}

//蓝牙读取
static void bluetooth_tty_event_cb(int fd) {
  int t_rcv[128];
  int n;

  n = myRead_nonblock(fd, t_rcv, 7 * sizeof(int));
  if (n <= 0) {
    printf("close bluetooth tty fd\n");
    // task_delete_file(fd);
    // close(fd);
    exit(0);
    return;
  } else {
    printf("message: %d %d %d %d %d %d %d\n", t_rcv[0], t_rcv[1], t_rcv[2],
           t_rcv[3], t_rcv[4], t_rcv[5], t_rcv[6]);
    switch (t_rcv[0]) {
    case 0: {
      // start game
      int client_player = t_rcv[1];
      player = client_player;

      printf("start game, player %d\n", player);
    } break;
    case 1: {
      // restart game
      int client_player = t_rcv[1];
      player = client_player;

      printf("restart game, player %d\n", player);

      // redraw board
      draw_board();
      display_buttons();
      update();
    } break;
    case 2: {
      // receive win message
      int winner = t_rcv[1];
      printf("player %d win\n", winner);

    } break;
    case 3: {
      // receive pos message
      int chess_x = (t_rcv[1] >> 16) & 0xffff;
      int chess_y = t_rcv[1] & 0xffff;
      int rcv_player = t_rcv[2];
      printf("chess_x=%d, chess_y=%d\n", chess_x, chess_y);

      // draw chess
      draw_chess(chess_x, chess_y, rcv_player);

      update();
    } break;
    case 4: {
      // TODO: display error message
      int err = t_rcv[1];
      printf("error: %d\n", err);

    } break;
    }
  }

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

  // 打开多点触摸设备文件, 返回文件fd
  touch_fd = touch_init("/dev/input/event2");
  // 添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
  task_add_file(touch_fd, touch_event_cb);

  //蓝牙连接
  //读，读取服务端写入的信息
  bluetooth_fd1 = bluetooth_tty_init("/dev/rfcomm1");
  if (bluetooth_fd1 == -1)
    return 0;
  task_add_file(bluetooth_fd1, bluetooth_tty_event_cb);
  //写，向服务端写入信息
  bluetooth_fd2 = bluetooth_tty_init("/dev/rfcomm0");
  if (bluetooth_fd2 == -1)
    return 0;

  task_loop(); // 进入任务循环
  return 0;
}