#include "utils_tests.h"

START_TEST(test_remove_matrix_ok) {
  int rows = 5;
  int columns = 10;
  int **matrix = create_matrix(rows, columns);
  ck_assert_ptr_nonnull(matrix);
  matrix = remove_matrix(matrix, rows);
  ck_assert_ptr_null(matrix);
}

START_TEST(test_remove_matrix_null) {
  int **matrix = NULL;
  remove_matrix(NULL, 5);
  ck_assert_ptr_null(matrix);
}

START_TEST(test_remove_matrix_negative) {
  int rows = 5;
  int columns = 10;
  int **matrix = create_matrix(rows, columns);
  ck_assert_ptr_nonnull(matrix);
  matrix = remove_matrix(matrix, -1);
  ck_assert_ptr_nonnull(matrix);
  matrix = remove_matrix(matrix, rows);
  ck_assert_ptr_null(matrix);
}

Suite *remove_matrix_suite() {
  Suite *s = suite_create("utils_remove_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_remove_matrix_ok);
  tcase_add_test(tc_core, test_remove_matrix_null);
  tcase_add_test(tc_core, test_remove_matrix_negative);

  suite_add_tcase(s, tc_core);
  return s;
}