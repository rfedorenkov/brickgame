#include "../../inc/gui/interface.h"

Screen_t *init_interface(const char *title, int field_height, int field_width) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  init_colors();
  refresh();

  Screen_t *screen = calloc(1, sizeof(Screen_t));
  if (screen != NULL) {
    screen->title = title;
    screen->field_height = field_height;
    screen->field_width = field_width;

    int start_x = 1;
    int start_y = 1;

    screen->game_field = newwin(screen->field_height + 2,
                                screen->field_width * 2 + 2, start_y, start_x);

    screen->game_stats = newwin(5, screen->field_width * 2 + 5, start_y,
                                start_x + screen->field_width * 2 + 2);

    screen->next_figure = newwin(6, screen->field_width * 2 + 5, start_y + 5,
                                 start_x + screen->field_width * 2 + 2);

    screen->game_help =
        newwin(screen->field_height / 2 - 1, screen->field_width * 2 + 5,
               start_y + 11, start_x + screen->field_width * 2 + 2);

    screen->logo = newwin(screen->field_height / 2, screen->field_width * 2 + 5,
                          start_y + 19, start_x + screen->field_width * 2 + 2);
  }
  return screen;
}

void init_colors(void) {
  start_color();
  int colors[] = {COLOR_WHITE,   COLOR_CYAN, COLOR_GREEN, COLOR_YELLOW,
                  COLOR_MAGENTA, COLOR_BLUE, COLOR_RED};
  for (int i = 0; i < 7; i++) {
    init_pair(i + 1, COLOR_BLACK, colors[i]);
  }
  init_pair(7, COLOR_WHITE, COLOR_BLUE);
}

void destroy_interface(Screen_t *screen) {
  delwin(screen->game_field);
  delwin(screen->game_stats);
  delwin(screen->next_figure);
  delwin(screen->game_help);
  free(screen);
  endwin();
}

void refresh_windows(Screen_t *screen) {
  wrefresh(screen->game_field);
  wrefresh(screen->game_stats);
  wrefresh(screen->game_help);
  wrefresh(screen->next_figure);
}

void print_centered(WINDOW *window, int y, const char **text, int count) {
  for (int i = 0; i < count; i++) {
    int x = (getmaxx(window) - strlen(text[i])) / 2;
    mvwprintw(window, y + i, x, "%s", text[i]);
  }
  wrefresh(window);
}

void draw_windows(Screen_t *screen) {
  box(screen->game_field, 0, 0);
  box(screen->game_stats, 0, 0);
  box(screen->next_figure, 0, 0);
  box(screen->game_help, 0, 0);

  const char *message[] = {screen->title, "Stats", "Next figure", "Help"};

  print_centered(screen->game_field, 0, &message[0], 1);
  print_centered(screen->game_stats, 0, &message[1], 1);
  print_centered(screen->next_figure, 0, &message[2], 1);
  print_centered(screen->game_help, 0, &message[3], 1);

  refresh_windows(screen);
}

void draw_menu(Screen_t *screen) {
  const char *message[] = {"Press ENTER to start", "Press ESC to exit"};
  print_centered(screen->game_field, screen->field_height / 2 + 1, message, 2);
}

void draw_pause(Screen_t *screen) {
  const char *message[] = {"== PAUSE ==", "Press P to resume"};
  print_centered(screen->game_field, screen->field_height / 2 + 1, message, 2);
}

void draw_game_over(Screen_t *screen) {
  const char *message[] = {"== GAME OVER ==", "Press any key to close"};
  print_centered(screen->game_field, screen->field_height / 2 + 1, message, 2);
}

void draw_stats(Screen_t *screen, int high_score, int score, int level) {
  int x_text = 2;
  int x_number = 15;
  mvwprintw(screen->game_stats, 1, x_text, "High scores:");
  mvwprintw(screen->game_stats, 1, x_number, "%8d", high_score);
  mvwprintw(screen->game_stats, 2, x_text, "Score:");
  mvwprintw(screen->game_stats, 2, x_number, "%8d", score);
  mvwprintw(screen->game_stats, 3, x_text, "Level:");
  mvwprintw(screen->game_stats, 3, x_number, "%8d", level);
}

void draw_help(Screen_t *screen, const char **lines, int count) {
  for (int i = 0; i < count; i++) {
    mvwprintw(screen->game_help, i + 1, 2, "%s", lines[i]);
  }
}

void draw_logo(Screen_t *screen) {
  mvwprintw(screen->logo, 1, 2, "Developed by hisakoha");
  wrefresh(screen->logo);
}

void draw_field(Screen_t *screen, int **field) {
  for (int y = 0; y < screen->field_height; y++) {
    for (int x = 0; x < screen->field_width; x++) {
      int color = field[y][x] != 0 ? field[y][x] : 8;
      wattron(screen->game_field, COLOR_PAIR(color));
      mvwprintw(screen->game_field, y + 1, x * 2 + 1, "  ");
      wattroff(screen->game_field, COLOR_PAIR(color));
    }
  }
  wrefresh(screen->game_field);
}

void draw_figure(Screen_t *screen, int **figure, int x_start, int y_start,
                 int size) {
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (figure[y][x]) {
        if (y_start + y >= 0) {
          wattron(screen->game_field, COLOR_PAIR(figure[y][x]));
          mvwprintw(screen->game_field, y_start + y + 1, (x_start + x) * 2 + 1,
                    "  ");
          wattroff(screen->game_field, COLOR_PAIR(figure[y][x]));
        }
      }
    }
  }
  wrefresh(screen->game_field);
}

void draw_next_figure(Screen_t *screen, int **figure, int size) {
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      int color = figure[y][x] != 0 ? (figure[y][x]) : 8;
      wattron(screen->next_figure, COLOR_PAIR(color));
      mvwprintw(screen->next_figure, y + 1, x * 2 + 8, "  ");
      wattroff(screen->next_figure, COLOR_PAIR(color));
    }
  }
  wrefresh(screen->next_figure);
}
