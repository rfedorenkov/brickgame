#include "utils_tests.h"

START_TEST(test_get_current_time_one_ms) {
  long long t1 = get_current_time();
  usleep(1000);
  long long t2 = get_current_time();
  ck_assert_int_ge(t2, t1);
}

START_TEST(test_get_current_time_delta) {
  long long t1 = get_current_time();
  usleep(10000);
  long long t2 = get_current_time();
  long long delta = t2 - t1;
  ck_assert_int_ge(delta, 5);
  ck_assert_int_le(delta, 15);
}

Suite *get_current_time_suite() {
  Suite *s = suite_create("utils_get_current_time");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_get_current_time_one_ms);
  tcase_add_test(tc_core, test_get_current_time_delta);

  suite_add_tcase(s, tc_core);
  return s;
}
