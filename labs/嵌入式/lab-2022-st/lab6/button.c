#include "button.h"
#include <stdlib.h>
#include <string.h>

static button_t buttons[MAX_BUTTON_NUM];
static int last_button = -1;

void init_button() {
  for (int i = 0; i < 10; i++) {
    buttons[i].x = 0;
    buttons[i].y = 0;
    buttons[i].w = 0;
    buttons[i].h = 0;
    buttons[i].bgcolor = 0;
    buttons[i].fontcolor = 0;
    memset(buttons[i].text, 0, sizeof(buttons[i].text));
    buttons[i].pressed = 0;
  }
  return;
}

int register_button(int x, int y, int w, int h, int bgcolor, int fontcolor, char *text) {
  if (last_button >= MAX_BUTTON_NUM - 1)
    return -1;
  last_button++;
  buttons[last_button].x = x;
  buttons[last_button].y = y;
  buttons[last_button].w = w;
  buttons[last_button].h = h;
  buttons[last_button].bgcolor = bgcolor;
  buttons[last_button].fontcolor = fontcolor;
  strcpy(buttons[last_button].text, text);
  buttons[last_button].pressed = 0;
  return last_button;
}

button_t *press_button(int x, int y) {
  for (int i = 0; i <= last_button; i++) {
    if (x >= buttons[i].x && x < buttons[i].x + buttons[i].w &&
        y >= buttons[i].y && y < buttons[i].y + buttons[i].h) {
      buttons[i].pressed = 1;
      return &buttons[i];
    }
  }
  return NULL;
}

button_t *release_button(int x, int y) {
  for (int i = 0; i <= last_button; i++) {
    if (x >= buttons[i].x && x < buttons[i].x + buttons[i].w &&
        y >= buttons[i].y && y < buttons[i].y + buttons[i].h) {
      buttons[i].pressed = 0;
      return &buttons[i];
    }
  }
  return NULL;
}

static void display_button(button_t *button) {
  if (button->pressed)
    draw_button_pressed(button->x, button->y, button->w, button->h,
                        button->bgcolor, button->fontcolor, button->text);
  else
    draw_button(button->x, button->y, button->w, button->h, button->bgcolor,
                button->fontcolor, button->text);
  return;
}

void display_buttons() {
  for (int i = 0; i <= last_button; i++) {
    display_button(&buttons[i]);
  }
  return;
}