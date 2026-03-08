#include "fsm_tests.h"

START_TEST(test_is_game_over_false) {
  GameModel_t *model = get_current_model();
  model->state = GS_Shifting;
  ck_assert_int_eq(is_game_over(), 0);
}

START_TEST(test_is_game_over_true) {
  GameModel_t *model = get_current_model();
  model->state = GS_Over;
  ck_assert_int_eq(is_game_over(), 1);
}

Suite *is_game_over_suite() {
  Suite *s = suite_create("fsm_is_game_over");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_game_over_false);
  tcase_add_test(tc_core, test_is_game_over_true);
  suite_add_tcase(s, tc_core);
  return s;
}