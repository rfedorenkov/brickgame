#include "../../inc/backend/fsm.h"

GameInfo_t updateCurrentState(void) {
  GameModel_t* model = get_current_model();
  if (model->state == GS_Spawn) {
    generate_figure();
    if (check_collision(model, 0, -1)) {
      model->state = GS_Over;
    } else {
      model->state = GS_Moving;
    }
  } else if (model->state == GS_Shifting) {
    model->figure_y++;
    model->state = GS_Moving;
  } else if (model->state == GS_Attaching) {
    if (check_collision(model, 0, 1)) {
      lock_figure(model);
      int count_lines = remove_lines_on_field(model->info);
      update_score_and_level(model->info, count_lines);
      model->state = GS_Spawn;
    } else {
      model->state = GS_Moving;
    }
  }
  return *model->info;
}

bool is_action_allowed(UserAction_t action) {
  bool flag = false;
  switch (action) {
    case Start:
      flag = !is_started();
      break;
    case Terminate:
      flag = true;
      break;
    case Pause:
      flag = is_started();
      break;
    case Left:
    case Right:
    case Down:
    case Action:
      flag = is_started() && !is_paused();
      break;
    default:
      flag = false;
  }
  return flag;
}

void userInput(UserAction_t action, bool hold) {
  GameModel_t* model = get_current_model();
  if (model->state == GS_Start && action == Start) {
    start(model);
    model->state = GS_Spawn;
  } else if (!hold && action == Terminate) {
    model->state = GS_Exit;
  } else if (!hold && action == Pause) {
    pause_game(model->info, model->state);
  } else if (is_started() && !is_paused()) {
    if (hold && action == Left) {
      move_left(model);
    } else if (hold && action == Right) {
      move_right(model);
    } else if (action == Down) {
      drop_down(model);
    } else if (action == Action) {
      rotate(model);
    }
  }
}

bool is_started() { return get_current_model()->state != GS_Start; }

bool is_paused() {
  GameModel_t* model = get_current_model();
  return model->info != NULL && model->info->pause == 1;
}

bool is_game_over() { return get_current_model()->state == GS_Over; }

bool is_exit() { return get_current_model()->state == GS_Exit; }

void start(GameModel_t* model) { model->info->pause = 0; }

void pause_game(GameInfo_t* info, GameState_t state) {
  if (state != GS_Start && state != GS_Over) {
    info->pause = !info->pause;
  }
}

void game_over() {
  GameModel_t* model = get_current_model();
  model->state = GS_Over;
  GameInfo_t* info = model->info;
  info->pause = 0;
  info->field = remove_matrix(info->field, FIELD_HEIGHT);
  info->next = remove_matrix(info->next, FIGURE_SIZE);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  free(info);
  get_current_model()->info = NULL;
}