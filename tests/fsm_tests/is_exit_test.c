#include "fsm_tests.h"

START_TEST(test_is_exit_false) {
  GameModel_t *model = get_current_model();
  model->state = GS_Shifting;
  ck_assert_int_eq(is_exit(), 0);
}

START_TEST(test_is_exit_true) {
  GameModel_t *model = get_current_model();
  model->state = GS_Exit;
  ck_assert_int_eq(is_exit(), 1);
}

Suite *is_exit_suite() {
  Suite *s = suite_create("fsm_is_exit");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_exit_false);
  tcase_add_test(tc_core, test_is_exit_true);
  suite_add_tcase(s, tc_core);
  return s;
}