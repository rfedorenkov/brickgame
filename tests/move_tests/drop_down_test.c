#include "move_tests.h"

START_TEST(test_drop_down_ok) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = FIELD_HEIGHT - 1;
  model->figure_y = y;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  drop_down(model);
  updateCurrentState();
  ck_assert_int_eq(model->figure_y, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_move_drop_block_collision) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = FIELD_HEIGHT - 2;
  model->figure_y = y;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;
  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  info.field[FIELD_HEIGHT - 1][0] = 1;
  drop_down(model);
  updateCurrentState();
  ck_assert_int_eq(model->figure_y, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_move_drop_model_null) { drop_down(NULL); }

START_TEST(test_move_drop_model_figure_null) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = 0;
  model->figure_y = y;
  model->figure = NULL;
  GameInfo_t info = {0};
  model->info = &info;
  drop_down(model);
  ck_assert_int_eq(model->figure_y, exp);
}

START_TEST(test_move_drop_model_info_null) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  int y = 0;
  int exp = 0;
  model->figure_y = y;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->info = NULL;
  drop_down(model);
  ck_assert_int_eq(model->figure_y, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
}

Suite *drop_down_suite() {
  Suite *s = suite_create("move_drop_down");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_drop_down_ok);
  tcase_add_test(tc_core, test_move_drop_block_collision);
  tcase_add_test(tc_core, test_move_drop_model_null);
  tcase_add_test(tc_core, test_move_drop_model_figure_null);
  tcase_add_test(tc_core, test_move_drop_model_info_null);

  suite_add_tcase(s, tc_core);
  return s;
}
