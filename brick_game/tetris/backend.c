#include "../../inc/backend/backend.h"

GameModel_t* get_current_model(void) {
  static GameModel_t model;
  return &model;
}

void init_game(void) {
  srand(time(NULL));
  GameModel_t* model = get_current_model();
  if (model->info == NULL) {
    model->info = calloc(1, sizeof(GameInfo_t));
  }

  init_game_info(model->info);
  init_fields(model->info);

  model->state = GS_Start;
  model->figure = NULL;
  model->figure_x = FIELD_WIDTH / 2;
  model->figure_y = 0;
  model->figure_id = 0;
  model->next_figure_id = 0;
  model->last_time = 0;
  model->interval = 500;
}

void init_game_info(GameInfo_t* info) {
  if (info != NULL) {
    info->score = 0;
    info->level = MIN_LEVEL;
    info->speed = START_SPEED;
    info->pause = 0;
    info->high_score = 0;
    if (load_high_score_file(&info->high_score) == -1) {
      save_high_score_file(info->high_score);
    }
  }
}

void init_fields(GameInfo_t* info) {
  if (info != NULL) {
    info->field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
    info->next = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
    if (info->field != NULL && info->next != NULL) {
      generate_random_figure(info);
    }
  }
}
