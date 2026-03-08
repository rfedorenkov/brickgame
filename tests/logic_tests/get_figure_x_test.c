#include "logic_tests.h"

START_TEST(test_get_figure_x_ok) {
  GameModel_t *model = get_current_model();
  int exp = 5;
  model->figure_x = exp;
  int x = get_figure_x();
  ck_assert_int_eq(x, exp);
}

Suite *get_figure_x_suite() {
  Suite *s = suite_create("logic_get_figure_x");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_get_figure_x_ok);
  suite_add_tcase(s, tc_core);
  return s;
}
