#include "logic_tests.h"

START_TEST(test_check_collision_no_collision) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = 5;
  model->figure_y = 0;
  model->figure[0][0] = 1;

  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  model->info = &info;

  bool result = check_collision(model, -1, 0);
  ck_assert_int_eq(result, 0);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_check_collision_left_wall) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = 0;
  model->figure_y = 0;
  model->figure[0][0] = 1;

  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  model->info = &info;

  bool result = check_collision(model, -1, 0);
  ck_assert_int_eq(result, 1);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_check_collision_right_wall) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = FIELD_WIDTH - 1;
  model->figure_y = 0;
  model->figure[0][0] = 1;

  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  model->info = &info;

  bool result = check_collision(model, 1, 0);
  ck_assert_int_eq(result, 1);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_check_collision_block) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = 0;
  model->figure_y = 0;
  model->figure[0][0] = 1;

  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  info.field[1][0] = 1;

  model->info = &info;

  bool result = check_collision(model, 0, 1);
  ck_assert_int_eq(result, 1);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_check_collision_down_wall) {
  GameModel_t *model = get_current_model();
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);

  model->figure_x = 0;
  model->figure_y = FIELD_HEIGHT - 1;
  model->figure[0][0] = 1;

  GameInfo_t info = {0};
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  model->info = &info;

  bool result = check_collision(model, 0, 1);
  ck_assert_int_eq(result, 1);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(info.field);
}

START_TEST(test_check_collision_model_null) {
  bool result = check_collision(NULL, 0, 1);
  ck_assert_int_eq(result, 0);
}

Suite *check_collision_suite() {
  Suite *s = suite_create("logic_check_collision");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_check_collision_no_collision);
  tcase_add_test(tc_core, test_check_collision_left_wall);
  tcase_add_test(tc_core, test_check_collision_right_wall);
  tcase_add_test(tc_core, test_check_collision_block);
  tcase_add_test(tc_core, test_check_collision_down_wall);
  tcase_add_test(tc_core, test_check_collision_model_null);
  suite_add_tcase(s, tc_core);
  return s;
}