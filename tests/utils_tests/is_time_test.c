#include "utils_tests.h"

START_TEST(test_is_time_true) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  info.speed = 10;
  model->info = &info;
  model->last_time = get_current_time() - 20;
  ck_assert(is_time() == true);
}

START_TEST(test_is_time_false) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  info.speed = 10;
  model->info = &info;
  model->last_time = get_current_time() + 10;
  ck_assert(is_time() == false);
}

START_TEST(test_is_time_model_info_null_false) {
  GameModel_t *model = get_current_model();
  model->info = NULL;
  ck_assert(is_time() == false);
}

Suite *is_time_suite() {
  Suite *s = suite_create("utils_is_time");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_time_true);
  tcase_add_test(tc_core, test_is_time_false);
  tcase_add_test(tc_core, test_is_time_model_info_null_false);

  suite_add_tcase(s, tc_core);
  return s;
}
