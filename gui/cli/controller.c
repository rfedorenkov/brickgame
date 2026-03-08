#include "../../inc/gui/controller.h"

void start_game(void) {
  init_game();
  GameSettings_t game_settings = get_default_settings();

  InterfaceContext_t *ctx = calloc(1, sizeof(InterfaceContext_t));
  if (ctx != NULL) {
    ctx->screen = init_interface(game_settings.title, game_settings.height,
                                 game_settings.width);
    ctx->keys = get_default_keys();
    ctx->game_info = updateCurrentState();

    game_loop(ctx);
    free(ctx->keys);
    destroy_interface(ctx->screen);
    free(ctx);
    game_over();
  }
}

GameSettings_t get_default_settings(void) {
  GameSettings_t game_settings = {
      .title = GAME_NAME, .height = FIELD_HEIGHT, .width = FIELD_WIDTH};
  return game_settings;
}

void game_loop(InterfaceContext_t *ctx) {
  set_escdelay(50);

  int ch = 0;
  while (!(is_game_over() || is_exit())) {
    ch = getch();
    handle_input(ch, ctx);
    ctx->game_info = updateCurrentState();
    if (!is_paused() && is_time()) {
      move_down();
    }
    if (!is_exit()) {
      fill_interface(ctx);
    }
    usleep(1000);
  }
  if (is_game_over()) {
    draw_game_over(ctx->screen);
    nodelay(stdscr, FALSE);
    ch = getch();
  }
}

void handle_input(int ch, InterfaceContext_t *ctx) {
  int find = 0;
  for (int i = 0; i <= Action && !find; i++) {
    if (ctx->keys[i].key == ch) {
      if (is_action_allowed(ctx->keys[i].action)) {
        userInput(ctx->keys[i].action, ctx->keys[i].hold);
        find = 1;
      }
    }
  }
}

keymap_t *get_default_keys(void) {
  keymap_t *keys = calloc(Action + 1, sizeof(keymap_t));
  if (keys != NULL) {
    keys[Start] = (keymap_t){'\n', Start, "Start game", "Enter", false};
    keys[Terminate] = (keymap_t){27, Terminate, "Exit", "ESC", false};
    keys[Pause] = (keymap_t){'p', Pause, "Pause", "p", false};
    keys[Left] = (keymap_t){KEY_LEFT, Left, "Move left", "◀️", true};
    keys[Right] = (keymap_t){KEY_RIGHT, Right, "Move right", "▶️", true};
    keys[Up] = (keymap_t){0, Up, "Unused", "", false};
    keys[Down] = (keymap_t){KEY_DOWN, Down, "Hard drop", "🔽", false};
    keys[Action] = (keymap_t){' ', Action, "Rotate", "Space", false};
  }
  return keys;
}

void fill_interface(InterfaceContext_t *ctx) {
  draw_windows(ctx->screen);
  draw_stats(ctx->screen, ctx->game_info.high_score, ctx->game_info.score,
             ctx->game_info.level);
  if (!is_started()) {
    draw_menu(ctx->screen);
  } else if (is_paused()) {
    draw_pause(ctx->screen);
  } else {
    draw_field(ctx->screen, ctx->game_info.field);
    draw_figure(ctx->screen, get_current_figure(), get_figure_x(),
                get_figure_y(), FIGURE_SIZE);
    draw_next_figure(ctx->screen, updateCurrentState().next, FIGURE_SIZE);
  }
  draw_logo(ctx->screen);
  fill_help_with_keys(ctx);
  refresh_windows(ctx->screen);
}

void fill_help_with_keys(InterfaceContext_t *ctx) {
  int size = Action + 1;
  const char *lines[size];
  char buffer[size][64];
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (ctx->keys[i].icon[0] != '\0') {
      snprintf(buffer[count], sizeof(buffer[count]), "%-10.10s : %-6.6s",
               ctx->keys[i].description, ctx->keys[i].icon);
      lines[count] = buffer[count];
      count++;
    }
  }

  draw_help(ctx->screen, lines, count);
}