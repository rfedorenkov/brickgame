#include "logic_tests.h"

START_TEST(test_get_figure_y_ok) {
  GameModel_t *model = get_current_model();
  int exp = 5;
  model->figure_y = exp;
  int y = get_figure_y();
  ck_assert_int_eq(y, exp);
}

Suite *get_figure_y_suite() {
  Suite *s = suite_create("logic_get_figure_y");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_get_figure_y_ok);
  suite_add_tcase(s, tc_core);
  return s;
}
