#include "logic_tests.h"

START_TEST(test_check_generate_figure) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;

  info.next = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  const int(*fixed_figure)[FIGURE_SIZE] = get_available_figure(0);
  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      info.next[y][x] = fixed_figure[y][x];
    }
  }

  model->next_figure_id = 0;

  model->figure = NULL;
  generate_figure();

  ck_assert_int_eq(model->figure_x, FIGURE_START_X);
  ck_assert_int_eq(model->figure_y, FIGURE_START_Y);

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      ck_assert_int_eq(model->figure[y][x], fixed_figure[y][x]);
    }
  }

  info.next = remove_matrix(info.next, FIGURE_SIZE);
  ck_assert_ptr_null(info.next);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_check_generate_figure_model_info_null) {
  GameModel_t *model = get_current_model();
  model->info = NULL;
  generate_figure();
  ck_assert_ptr_null(model->figure);
}

Suite *generate_figure_suite() {
  Suite *s = suite_create("logic_generate_figure");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_check_generate_figure);
  tcase_add_test(tc_core, test_check_generate_figure_model_info_null);
  suite_add_tcase(s, tc_core);
  return s;
}