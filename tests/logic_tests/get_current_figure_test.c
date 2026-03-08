#include "logic_tests.h"

START_TEST(test_get_current_figure_ok) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  const int(*figure)[FIGURE_SIZE] = get_available_figure(2);
  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      model->figure[y][x] = figure[y][x];
    }
  }

  int **exp_figure = get_current_figure();

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      ck_assert_int_eq(model->figure[y][x], exp_figure[y][x]);
    }
  }

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
}

Suite *get_current_figure_suite() {
  Suite *s = suite_create("logic_get_current_figure");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_get_current_figure_ok);
  suite_add_tcase(s, tc_core);
  return s;
}
