#include "move_tests.h"

START_TEST(test_move_right_ok) {
  GameModel_t *model = get_current_model();
  int x = 5;
  int exp = 6;
  model->figure_x = x;
  move_right(model);
  ck_assert_int_eq(model->figure_x, exp);
}

START_TEST(test_move_right_wall_collision) {
  GameModel_t *model = get_current_model();
  int x = FIELD_WIDTH - 1;
  int exp = FIELD_WIDTH - 1;
  model->figure_x = x;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  move_right(model);
  ck_assert_int_eq(model->figure_x, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_move_right_block_collision) {
  GameModel_t *model = get_current_model();
  int x = 5;
  int exp = 5;
  model->figure_x = x;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  int block_x = 6;
  info.field[0][block_x] = 1;
  move_right(model);
  ck_assert_int_eq(model->figure_x, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(model->figure, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_move_right_null) { move_right(NULL); }

Suite *move_right_suite() {
  Suite *s = suite_create("move_move_right");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_move_right_ok);
  tcase_add_test(tc_core, test_move_right_wall_collision);
  tcase_add_test(tc_core, test_move_right_block_collision);
  tcase_add_test(tc_core, test_move_right_null);

  suite_add_tcase(s, tc_core);
  return s;
}
