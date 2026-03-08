#include "../../inc/backend/logic.h"

void lock_figure(GameModel_t* model) {
  if (model != NULL && model->figure != NULL && model->info != NULL) {
    int** figure = model->figure;
    int** field = model->info->field;

    for (int dy = 0; dy < FIGURE_SIZE; dy++) {
      for (int dx = 0; dx < FIGURE_SIZE; dx++) {
        if (figure[dy][dx] != 0) {
          int x = model->figure_x + dx;
          int y = model->figure_y + dy;
          if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
            field[y][x] = figure[dy][dx];
          }
        }
      }
    }
  }
}

int remove_lines_on_field(GameInfo_t* info) {
  int count = 0;
  if (info != NULL && info->field != NULL) {
    for (int y = FIELD_HEIGHT - 1; y >= 0; y--) {
      bool is_full_line = true;
      for (int x = 0; x < FIELD_WIDTH && is_full_line; x++) {
        if (info->field[y][x] == 0) {
          is_full_line = false;
        }
      }

      if (is_full_line) {
        for (int i = y; i > 0; i--) {
          for (int j = 0; j < FIELD_WIDTH; j++) {
            info->field[i][j] = info->field[i - 1][j];
          }
        }
        for (int x = 0; x < FIELD_WIDTH; x++) {
          info->field[0][x] = 0;
        }
        count++;
        y++;
      }
    }
  }
  return count;
}

void update_score_and_level(GameInfo_t* info, int count) {
  if (info != NULL) {
    count = (count < 1 || count > 4) ? 0 : count;
    int score_table[] = {0, 100, 300, 700, 1500};
    info->score += score_table[count];
    int level = info->score / SCORE_PER_LEVEL + 1;
    info->level = (level > MAX_LEVEL) ? MAX_LEVEL : level;

    if (info->high_score < info->score) {
      info->high_score = info->score;
      save_high_score_file(info->high_score);
    }

    info->speed = START_SPEED - (info->level - 1) * SPEED_STEP;
  }
}

bool check_collision(GameModel_t* model, int start_x, int start_y) {
  bool collision = false;
  if (model != NULL && model->info != NULL && model->figure != NULL) {
    int** figure = model->figure;
    int** field = model->info->field;

    for (int dy = 0; dy < FIGURE_SIZE && !collision; dy++) {
      for (int dx = 0; dx < FIGURE_SIZE && !collision; dx++) {
        if (figure[dy][dx] != 0) {
          int x = model->figure_x + start_x + dx;
          int y = model->figure_y + start_y + dy;
          if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT) {
            collision = true;
          } else if (y >= 0 && field[y][x] != 0) {
            collision = true;
          }
        }
      }
    }
  }
  return collision;
}

const int (*get_available_figure(int id))[FIGURE_SIZE] {
  static const int figures[FIGURE_COUNT][FIGURE_SIZE][FIGURE_SIZE] = {
      // I
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // J
      {{0, 0, 0, 0}, {0, 2, 0, 0}, {0, 2, 2, 2}, {0, 0, 0, 0}},
      // L
      {{0, 0, 0, 0}, {0, 0, 0, 3}, {0, 3, 3, 3}, {0, 0, 0, 0}},
      // O
      {{0, 0, 0, 0}, {0, 4, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
      // S
      {{0, 0, 0, 0}, {0, 0, 5, 5}, {0, 5, 5, 0}, {0, 0, 0, 0}},
      // T
      {{0, 0, 0, 0}, {0, 0, 6, 0}, {0, 6, 6, 6}, {0, 0, 0, 0}},
      // Z
      {{0, 0, 0, 0}, {0, 7, 7, 0}, {0, 0, 7, 7}, {0, 0, 0, 0}},
  };

  return figures[id];
}

void generate_random_figure(GameInfo_t* info) {
  if (info != NULL && info->next != NULL) {
    int id = rand() % FIGURE_COUNT;
    const int(*figure)[FIGURE_SIZE] = get_available_figure(id);
    for (int y = 0; y < FIGURE_SIZE; y++) {
      for (int x = 0; x < FIGURE_SIZE; x++) {
        info->next[y][x] = figure[y][x];
      }
    }

    GameModel_t* model = get_current_model();
    model->next_figure_id = id;
  }
}

void generate_figure(void) {
  GameModel_t* model = get_current_model();
  if (model != NULL && model->info != NULL && model->info->next != NULL) {
    int** new_figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
    if (new_figure != NULL) {
      for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
          new_figure[i][j] = model->info->next[i][j];
        }
      }

      int** old_figure = model->figure;
      model->figure = new_figure;
      model->figure_x = FIGURE_START_X;
      model->figure_y = FIGURE_START_Y;

      model->figure_id = model->next_figure_id;

      generate_random_figure(model->info);

      if (old_figure != NULL) {
        remove_matrix(old_figure, FIGURE_SIZE);
      }
    }
  }
}

int** get_current_figure(void) { return get_current_model()->figure; }

int get_figure_x(void) { return get_current_model()->figure_x; }

int get_figure_y(void) { return get_current_model()->figure_y; }