#include "storage_tests.h"

START_TEST(test_load_high_score_file_ok) {
  save_high_score_file(100500);
  int n = -1;
  int error = load_high_score_file(&n);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(n, 100500);
}

START_TEST(test_load_high_score_no_file_error) {
  int n = -1;
  remove(HIGH_SCORE_FILE);
  int error = load_high_score_file(&n);
  ck_assert_int_eq(error, -1);
  save_high_score_file(100500);
}

START_TEST(test_load_high_score_file_wrong_data_error) {
  int n = -1;

  FILE *file = fopen(HIGH_SCORE_FILE, "w");
  fprintf(file, "wrong data\n");
  fclose(file);

  int error = load_high_score_file(&n);
  ck_assert_int_eq(error, -1);
  save_high_score_file(100500);
}

START_TEST(test_load_high_score_file_null) {
  int error = load_high_score_file(NULL);
  ck_assert_int_eq(error, -1);
}

Suite *load_high_score_file_ok_suite() {
  Suite *s = suite_create("storage_load_high_score_file");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_load_high_score_file_ok);
  tcase_add_test(tc_core, test_load_high_score_no_file_error);
  tcase_add_test(tc_core, test_load_high_score_file_wrong_data_error);
  tcase_add_test(tc_core, test_load_high_score_file_null);

  suite_add_tcase(s, tc_core);
  return s;
}
