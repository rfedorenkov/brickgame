#include "storage_tests.h"

START_TEST(test_save_high_score_file_ok) {
  int error = save_high_score_file(100500);
  ck_assert_int_eq(error, 0);
  int n = -1;
  error = load_high_score_file(&n);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(n, 100500);
}

START_TEST(test_save_high_score_file_negative) {
  remove(HIGH_SCORE_FILE);
  mkdir(HIGH_SCORE_FILE, 0700);
  int error = save_high_score_file(100);
  remove(HIGH_SCORE_FILE);
  ck_assert_int_eq(error, -1);
}

Suite *save_high_score_file_ok_suite() {
  Suite *s = suite_create("storage_save_high_score_file");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_save_high_score_file_ok);
  tcase_add_test(tc_core, test_save_high_score_file_negative);

  suite_add_tcase(s, tc_core);
  return s;
}
