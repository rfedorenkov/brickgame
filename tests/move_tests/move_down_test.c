#include "move_tests.h"

START_TEST(test_move_down_ok) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = 1;
  model->figure_y = y;
  GameInfo_t info = {0};
  model->info = &info;
  move_down();
  updateCurrentState();
  ck_assert_int_eq(model->figure_y, exp);
}

START_TEST(test_move_down_wall_collision) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = FIELD_HEIGHT - 1;
  int exp = FIELD_HEIGHT - 1;
  model->figure_y = y;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[3][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  move_down();
  updateCurrentState();
  ck_assert_int_eq(model->figure_y, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_move_down_block_collision) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = 0;
  model->figure_y = y;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  int block_y = 1;
  info.field[block_y][0] = 1;
  move_down();
  updateCurrentState();
  ck_assert_int_eq(model->figure_x, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(model->figure, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_move_down_wrong) {
  GameModel_t *model = get_current_model();
  model->state = GS_Over;
  int y = 0;
  int exp = 0;
  model->figure_y = y;
  GameInfo_t info = {0};
  model->info = &info;
  move_down();
  updateCurrentState();
  ck_assert_int_eq(model->figure_y, exp);
}

Suite *move_down_suite() {
  Suite *s = suite_create("move_move_down");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_move_down_ok);
  tcase_add_test(tc_core, test_move_down_wall_collision);
  tcase_add_test(tc_core, test_move_down_block_collision);
  tcase_add_test(tc_core, test_move_down_wrong);

  suite_add_tcase(s, tc_core);
  return s;
}
