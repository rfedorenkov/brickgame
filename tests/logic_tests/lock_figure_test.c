#include "logic_tests.h"

START_TEST(test_lock_figure_ok) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = 0;
  model->figure_y = 0;

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      model->figure[y][x] = 1;
    }
  }
  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  model->info = &info;

  lock_figure(model);

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      ck_assert_int_eq(model->figure[y][x], info.field[y][x]);
    }
  }

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_lock_figure_model_null) { lock_figure(NULL); }

START_TEST(test_lock_figure_model_figure_null) {
  GameModel_t *model = get_current_model();
  model->figure = NULL;
  lock_figure(model);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_lock_figure_model_info_null) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->info = NULL;
  lock_figure(model);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  ck_assert_ptr_null(model->info);
}

Suite *lock_figure_suite() {
  Suite *s = suite_create("logic_lock_figure");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_lock_figure_ok);
  tcase_add_test(tc_core, test_lock_figure_model_null);
  tcase_add_test(tc_core, test_lock_figure_model_figure_null);
  tcase_add_test(tc_core, test_lock_figure_model_info_null);
  suite_add_tcase(s, tc_core);
  return s;
}
