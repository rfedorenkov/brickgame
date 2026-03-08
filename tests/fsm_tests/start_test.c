#include "fsm_tests.h"

START_TEST(test_start) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  info.pause = 1;
  start(model);
  ck_assert_int_eq(info.pause, 0);
}

Suite *start_suite() {
  Suite *s = suite_create("fsm_start");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_start);
  suite_add_tcase(s, tc_core);
  return s;
}