#include "utils_tests.h"

START_TEST(test_create_matrix_ok) {
  int rows = 5;
  int columns = 10;
  int** matrix = create_matrix(rows, columns);
  ck_assert_ptr_nonnull(matrix);
  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(matrix[i]);
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    }
  }
  matrix = remove_matrix(matrix, rows);
}

START_TEST(test_create_matrix_negative_size) {
  int rows = -5;
  int columns = -10;
  int** matrix = create_matrix(rows, columns);
  ck_assert_ptr_null(matrix);
}

START_TEST(test_create_matrix_negative_rows) {
  int rows = -5;
  int columns = 10;
  int** matrix = create_matrix(rows, columns);
  ck_assert_ptr_null(matrix);
}

START_TEST(test_create_matrix_negative_columns) {
  int rows = 5;
  int columns = -10;
  int** matrix = create_matrix(rows, columns);
  ck_assert_ptr_null(matrix);
}

START_TEST(test_create_matrix_memmory_error) {
  int rows = 100000000;
  int** matrix = create_matrix(rows, rows);
  ck_assert_ptr_null(matrix);
}

Suite* create_matrix_suite() {
  Suite* s = suite_create("utils_create_matrix");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_matrix_ok);
  tcase_add_test(tc_core, test_create_matrix_negative_size);
  tcase_add_test(tc_core, test_create_matrix_negative_rows);
  tcase_add_test(tc_core, test_create_matrix_negative_columns);
  tcase_add_test(tc_core, test_create_matrix_memmory_error);

  suite_add_tcase(s, tc_core);
  return s;
}
