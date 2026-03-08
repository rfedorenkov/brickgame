#include "fsm_tests.h"

START_TEST(test_game_over) {
  GameModel_t *model = get_current_model();
  GameInfo_t *info = calloc(1, sizeof(GameInfo_t));
  model->info = info;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  info->field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  info->next = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  game_over();
  ck_assert_int_eq(model->state, GS_Over);
  ck_assert_ptr_null(model->figure);
  ck_assert_ptr_null(model->info);
}

Suite *game_over_suite() {
  Suite *s = suite_create("fsm_game_over");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_game_over);
  suite_add_tcase(s, tc_core);
  return s;
}