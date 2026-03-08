#include "backend_tests.h"

START_TEST(test_init_fields) {
  GameInfo_t info = {0};
  ck_assert_ptr_null(info.field);
  ck_assert_ptr_null(info.next);
  init_fields(&info);
  ck_assert_ptr_nonnull(info.field);
  ck_assert_ptr_nonnull(info.next);

  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
  info.next = remove_matrix(info.field, FIGURE_SIZE);
  ck_assert_ptr_null(info.next);
}

START_TEST(test_init_fields_null) { init_fields(NULL); }

Suite *init_fields_suite() {
  Suite *s = suite_create("backend_init_fields");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_fields);
  tcase_add_test(tc_core, test_init_fields_null);
  suite_add_tcase(s, tc_core);
  return s;
}