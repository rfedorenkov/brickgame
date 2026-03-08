#include "logic_tests.h"

START_TEST(test_generate_random_figure) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  info.next = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  srand(0);
  generate_random_figure(&info);

  ck_assert_int_ge(model->next_figure_id, 0);
  ck_assert_int_lt(model->next_figure_id, FIGURE_COUNT);

  const int(*expected)[FIGURE_SIZE] =
      get_available_figure(model->next_figure_id);

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      ck_assert_int_eq(info.next[y][x], expected[y][x]);
    }
  }

  info.next = remove_matrix(info.next, FIGURE_SIZE);
  ck_assert_ptr_null(info.next);
}

START_TEST(test_generate_random_figure_info_null) {
  GameModel_t *model = get_current_model();
  model->info = NULL;
  model->figure_id = -99;

  srand(0);
  generate_random_figure(model->info);

  ck_assert_int_eq(model->figure_id, -99);
  ck_assert_ptr_null(model->info);
}

START_TEST(test_generate_random_figure_info_next_null) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  info.next = NULL;
  model->info = &info;
  model->figure_id = -99;

  srand(0);
  generate_random_figure(model->info);

  ck_assert_int_eq(model->figure_id, -99);
  ck_assert_ptr_null(info.next);
}

Suite *generate_random_figure_suite() {
  Suite *s = suite_create("logic_generate_random_figure");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_generate_random_figure);
  tcase_add_test(tc_core, test_generate_random_figure_info_null);
  tcase_add_test(tc_core, test_generate_random_figure_info_next_null);
  suite_add_tcase(s, tc_core);
  return s;
}