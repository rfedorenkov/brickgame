#include "../../inc/backend/move.h"

void move_left(GameModel_t* model) {
  if (model != NULL && !check_collision(model, -1, 0)) {
    model->figure_x -= 1;
  }
}

void move_right(GameModel_t* model) {
  if (model != NULL && !check_collision(model, 1, 0)) {
    model->figure_x += 1;
  }
}

void move_down() {
  GameModel_t* model = get_current_model();
  if (model->state == GS_Moving) {
    if (!check_collision(model, 0, 1)) {
      model->state = GS_Shifting;
    } else {
      model->state = GS_Attaching;
    }
  }
}

void drop_down(GameModel_t* model) {
  if (model != NULL && model->figure != NULL && model->info != NULL) {
    while (!check_collision(model, 0, 1)) {
      model->figure_y++;
    }
    model->state = GS_Attaching;
  }
}

void rotate(GameModel_t* model) {
  if (model != NULL && model->figure != NULL && model->info != NULL) {
    int** rotated = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
    if (rotated != NULL) {
      int** figure = model->figure;
      for (int y = 0; y < FIGURE_SIZE; y++) {
        for (int x = 0; x < FIGURE_SIZE; x++) {
          rotated[x][FIGURE_SIZE - y - 1] = figure[y][x];
        }
      }
      model->figure = rotated;
      if (!check_collision(model, 0, 0)) {
        remove_matrix(figure, FIGURE_SIZE);
      } else {
        model->figure = figure;
        remove_matrix(rotated, FIGURE_SIZE);
      }
    }
  }
}