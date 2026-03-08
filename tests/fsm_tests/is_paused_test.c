#include "fsm_tests.h"

START_TEST(test_is_paused_false) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  ck_assert_int_eq(is_paused(), 0);
}

START_TEST(test_is_paused_true) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Moving;
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 1);
}

START_TEST(test_is_paused_info_null) {
  GameModel_t *model = get_current_model();
  model->info = NULL;
  ck_assert_int_eq(is_paused(), 0);
}

Suite *is_paused_suite() {
  Suite *s = suite_create("fsm_is_paused");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_paused_false);
  tcase_add_test(tc_core, test_is_paused_true);
  tcase_add_test(tc_core, test_is_paused_info_null);
  suite_add_tcase(s, tc_core);
  return s;
}