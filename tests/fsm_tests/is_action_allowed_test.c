#include "fsm_tests.h"

START_TEST(test_is_action_allowed_start) {
  int exp = 1;
  ck_assert_int_eq(is_action_allowed(Start), exp);
}

START_TEST(test_is_action_allowed_terminate) {
  int exp = 1;
  ck_assert_int_eq(is_action_allowed(Terminate), exp);
}

START_TEST(test_is_action_allowed_moving) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;

  int exp = 0;
  ck_assert_int_eq(is_action_allowed(Left), exp);
  ck_assert_int_eq(is_action_allowed(Right), exp);
  ck_assert_int_eq(is_action_allowed(Down), exp);
  ck_assert_int_eq(is_action_allowed(Action), exp);

  start(model);
  model->state = GS_Moving;
  exp = 1;
  ck_assert_int_eq(is_action_allowed(Left), exp);
  ck_assert_int_eq(is_action_allowed(Right), exp);
  ck_assert_int_eq(is_action_allowed(Down), exp);
  ck_assert_int_eq(is_action_allowed(Action), exp);
}

START_TEST(test_is_action_allowed_pause) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;

  int exp = 0;
  ck_assert_int_eq(is_action_allowed(Pause), exp);

  start(model);
  model->state = GS_Moving;
  exp = 1;
  ck_assert_int_eq(is_action_allowed(Pause), exp);
}

START_TEST(test_is_action_allowed_wrong) {
  int exp = 0;
  ck_assert_int_eq(is_action_allowed(Up), exp);
}

Suite *is_action_allowed_suite() {
  Suite *s = suite_create("fsm_is_action_allowed");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_action_allowed_start);
  tcase_add_test(tc_core, test_is_action_allowed_terminate);
  tcase_add_test(tc_core, test_is_action_allowed_moving);
  tcase_add_test(tc_core, test_is_action_allowed_pause);
  tcase_add_test(tc_core, test_is_action_allowed_wrong);
  suite_add_tcase(s, tc_core);
  return s;
}