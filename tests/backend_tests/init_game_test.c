#include "backend_tests.h"

START_TEST(test_init_game) {
  GameModel_t *model = get_current_model();
  ck_assert_ptr_null(model->info);
  init_game();
  ck_assert_ptr_nonnull(model->info);
  ck_assert_int_eq(model->state, GS_Start);
  ck_assert_ptr_null(model->figure);
  ck_assert_int_eq(model->figure_x, FIELD_WIDTH / 2);
  ck_assert_int_eq(model->figure_y, 0);
  ck_assert_int_eq(model->figure_id, 0);
  ck_assert_int_eq(model->next_figure_id, 0);
  ck_assert_int_eq(model->last_time, 0);
  ck_assert_int_eq(model->interval, 500);
  ck_assert_int_eq(model->info->score, 0);
  ck_assert_int_eq(model->info->level, MIN_LEVEL);
  ck_assert_int_eq(model->info->speed, START_SPEED);

  game_over();
  ck_assert_ptr_null(model->info);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_init_game_info_notnull) {
  GameModel_t *model = get_current_model();
  GameInfo_t *info = calloc(1, sizeof(GameInfo_t));
  model->info = info;
  ck_assert_ptr_nonnull(model->info);
  init_game();
  ck_assert_int_eq(model->state, GS_Start);
  ck_assert_ptr_null(model->figure);
  ck_assert_int_eq(model->figure_x, FIELD_WIDTH / 2);
  ck_assert_int_eq(model->figure_y, 0);
  ck_assert_int_eq(model->figure_id, 0);
  ck_assert_int_eq(model->next_figure_id, 0);
  ck_assert_int_eq(model->last_time, 0);
  ck_assert_int_eq(model->interval, 500);
  ck_assert_int_eq(model->info->score, 0);
  ck_assert_int_eq(model->info->level, MIN_LEVEL);
  ck_assert_int_eq(model->info->speed, START_SPEED);

  game_over();
  ck_assert_ptr_null(model->info);
  ck_assert_ptr_null(model->figure);
}

Suite *init_game_suite() {
  Suite *s = suite_create("backend_init_game");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_game);
  tcase_add_test(tc_core, test_init_game_info_notnull);
  suite_add_tcase(s, tc_core);
  return s;
}