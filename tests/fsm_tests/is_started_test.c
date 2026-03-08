#include "fsm_tests.h"

START_TEST(test_is_started_false) {
  GameModel_t *model = get_current_model();
  model->state = GS_Start;
  ck_assert_int_eq(is_started(), 0);
}

START_TEST(test_is_started_true) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  ck_assert_int_eq(is_started(), 1);
}

Suite *is_started_suite() {
  Suite *s = suite_create("fsm_is_started");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_started_false);
  tcase_add_test(tc_core, test_is_started_true);
  suite_add_tcase(s, tc_core);
  return s;
}