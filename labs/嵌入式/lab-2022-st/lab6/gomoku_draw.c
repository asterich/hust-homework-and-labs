#include "gomoku_draw.h"


#include "utf8.h"
#include <stdio.h>


void draw_board() {
  fb_draw_rect(BOARD_X, BOARD_Y, BOARD_SIZE * OUTER_GRID_SIZE,
               BOARD_SIZE * OUTER_GRID_SIZE, BLUE);
  for (int x = BOARD_X + OUTER_GRID_SIZE / 2;
       x < BOARD_X + BOARD_SIZE * OUTER_GRID_SIZE; x += OUTER_GRID_SIZE) {
    fb_draw_line(x, BOARD_Y + OUTER_GRID_SIZE / 2, x,
                 BOARD_Y + BOARD_SIZE * OUTER_GRID_SIZE - OUTER_GRID_SIZE / 2,
                 COLOR_GRID);
  }
  for (int y = BOARD_Y + OUTER_GRID_SIZE / 2;
       y < BOARD_Y + BOARD_SIZE * OUTER_GRID_SIZE; y += OUTER_GRID_SIZE) {
    fb_draw_line(BOARD_X + OUTER_GRID_SIZE / 2, y,
                 BOARD_X + BOARD_SIZE * OUTER_GRID_SIZE - OUTER_GRID_SIZE / 2,
                 y, COLOR_GRID);
  }
  return;
}

void draw_chess(int chess_x, int chess_y, chess_t chess) {
  if (chess == NO_CHESS)
    return;
  if (chess_x < 0 || chess_x >= BOARD_SIZE || chess_y < 0 ||
      chess_y >= BOARD_SIZE)
    return;
  int color = (chess == BLACK_CHESS) ? BLACK : WHITE;
  fb_draw_circle(BOARD_X + OUTER_GRID_SIZE / 2 + chess_x * OUTER_GRID_SIZE,
                 BOARD_Y + OUTER_GRID_SIZE / 2 + chess_y * OUTER_GRID_SIZE,
                 CHESS_SIZE / 2, color);
  return;
}

void draw_button(int x, int y, int width, int height, int bgcolor,
                 int fontcolor, char *text) {
  fb_draw_rect(x, y, width, height, bgcolor);
  fb_draw_border(x, y, width, height, BLACK);
  int font_size = 20;
  fb_draw_text(x + width / 2 - strlen(text) * font_size / 2 / 2, y + height / 2,
               text, font_size, fontcolor);
  return;
}

void draw_button_pressed(int x, int y, int width, int height, int bgcolor,
                         int fontcolor, char *text) {
  int deeper_bgcolor = (char)(bgcolor >> 16) / 2 << 16 |
                       (char)(bgcolor >> 8) / 2 << 8 | (char)(bgcolor) / 2;
  fb_draw_rect(x, y, width, height, deeper_bgcolor);
  fb_draw_rect(x + 5, y + 5, width - 6, height - 6, bgcolor);
  fb_draw_border(x, y, width, height, BLACK);
  int font_size = 20;
  fb_draw_text(x + width / 2 - strlen(text) * font_size / 2 / 2 + 5,
               y + height / 2 + 5, text, font_size, fontcolor);
  return;
}

void draw_text(int x, int y, int width, int height, int font_size, int color, char *text) {
  fb_draw_text(x, y, text, font_size, color);
  return;
}

void draw_multiline_text(int x, int y, int width, int height, int font_size, int color, char c_text[]) {
    
    const char *current_ptr = c_text;
    utf8_int32_t codepoint = 0;
    const char *line_start = c_text;
    int line_width = 0;
    

    while (*current_ptr != '\0') {
        const char *next_ptr = utf8codepoint(current_ptr, &codepoint);

        // 假设每个码点占据固定宽度
        line_width += font_size; // 这里的计算方式可能需要根据实际情况调整

        if (line_width > width + font_size || codepoint == '\n') {
            size_t line_length = current_ptr - line_start;
            char *line = (char *)malloc(line_length + 1);
            strncpy(line, line_start, line_length);
            line[line_length] = '\0';

            printf("line: %s", line);

            draw_text(x, y, width, height, font_size, color, line);
            free(line);

            y += font_size; // 更新 y 坐标以绘制下一行
            line_start = next_ptr;
            line_width = 0;
        }

        if (codepoint == '\n') {
            line_start = next_ptr;
        }

        current_ptr = next_ptr;
    }

    // 绘制最后一行（如果有）
    if (line_start != current_ptr) {
        draw_text(x, y, width, height, font_size, color, line_start);
    }
}

void clear_bg(int x, int y, int width, int height) {
  fb_draw_rect(x, y, width, height, BLUE);
  fb_update();
  return;
}

void update() { fb_update(); }