#include "logic_tests.h"

START_TEST(test_remove_lines_on_field_ok) {
  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int y = FIELD_HEIGHT - 5; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      info.field[y][x] = 1;
    }
  }

  int count = remove_lines_on_field(&info);
  ck_assert_int_eq(count, 5);

  for (int y = FIELD_HEIGHT - 5; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      ck_assert_int_eq(info.field[y][x], 0);
    }
  }

  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_remove_lines_on_field_info_null) {
  int count = remove_lines_on_field(NULL);
  ck_assert_int_eq(count, 0);
}

START_TEST(test_remove_lines_on_field_field_null) {
  GameInfo_t info = {0};
  info.field = NULL;
  int count = remove_lines_on_field(&info);
  ck_assert_int_eq(count, 0);
}

START_TEST(test_remove_lines_on_field_zero) {
  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int y = FIELD_HEIGHT - 5; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH - 2; x++) {
      info.field[y][x] = 1;
    }
  }

  int count = remove_lines_on_field(&info);
  ck_assert_int_eq(count, 0);

  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

Suite *remove_lines_on_field_suite() {
  Suite *s = suite_create("logic_delete_lines");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_remove_lines_on_field_ok);
  tcase_add_test(tc_core, test_remove_lines_on_field_info_null);
  tcase_add_test(tc_core, test_remove_lines_on_field_field_null);
  tcase_add_test(tc_core, test_remove_lines_on_field_zero);
  suite_add_tcase(s, tc_core);
  return s;
}
