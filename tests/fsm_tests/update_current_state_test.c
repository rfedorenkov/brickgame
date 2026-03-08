#include "fsm_tests.h"

START_TEST(test_update_current_state_spawn) {
  GameModel_t *model = get_current_model();
  GameInfo_t *info = calloc(1, sizeof(GameInfo_t));
  model->info = info;
  model->state = GS_Spawn;
  updateCurrentState();
  ck_assert_int_eq(model->state, GS_Moving);
  game_over();
  ck_assert_ptr_null(model->info);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_update_current_state_spawn_over) {
  GameModel_t *model = get_current_model();
  GameInfo_t *info = calloc(1, sizeof(GameInfo_t));
  model->info = info;
  model->state = GS_Spawn;

  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      model->figure[y][x] = 1;
    }
  }

  info->field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int x = 0; x < FIELD_WIDTH; x++) {
    info->field[0][x] = 1;
  }

  updateCurrentState();
  ck_assert_int_eq(model->state, GS_Over);
  game_over();
  ck_assert_ptr_null(model->info);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_update_current_state_shifting) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Shifting;
  updateCurrentState();
  ck_assert_int_eq(model->state, GS_Moving);
  ck_assert_int_eq(model->figure_y, 1);
}

START_TEST(test_update_current_state_attaching_false) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Attaching;
  updateCurrentState();
  ck_assert_int_eq(model->state, GS_Moving);
}

START_TEST(test_update_current_state_attaching_correct) {
  GameModel_t *model = get_current_model();
  GameInfo_t *info = calloc(1, sizeof(GameInfo_t));
  model->info = info;
  model->state = GS_Attaching;

  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure_x = 0;
  model->figure_y = 0;

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      model->figure[y][x] = 1;
    }
  }

  info->field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  model->figure_y += 3;
  for (int x = 0; x < FIELD_WIDTH - 2; x++) {
    info->field[4][x] = 1;
  }

  updateCurrentState();
  ck_assert_int_eq(model->state, GS_Spawn);
  game_over();
  ck_assert_ptr_null(model->info);
  ck_assert_ptr_null(model->figure);
}

Suite *update_current_state_suite() {
  Suite *s = suite_create("fsm_update_current_test");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_update_current_state_spawn);
  tcase_add_test(tc_core, test_update_current_state_spawn_over);
  tcase_add_test(tc_core, test_update_current_state_shifting);
  tcase_add_test(tc_core, test_update_current_state_attaching_false);
  tcase_add_test(tc_core, test_update_current_state_attaching_correct);
  suite_add_tcase(s, tc_core);
  return s;
}