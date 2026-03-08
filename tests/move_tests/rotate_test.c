#include "move_tests.h"

START_TEST(test_rotate_ok) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  model->figure_x = 5;
  model->figure_y = 5;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[1][1] = 1;
  model->figure[1][2] = 1;

  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  rotate(model);

  int exp[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      ck_assert_int_eq(model->figure[i][j], exp[i][j]);
    }
  }

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);

  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_rotate_collision) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  model->figure_x = 0;
  model->figure_y = 0;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[1][1] = 1;
  model->figure[1][2] = 1;

  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);
  info.field[2][2] = 1;

  rotate(model);

  ck_assert_int_eq(model->figure[1][1], 1);
  ck_assert_int_eq(model->figure[1][2], 1);

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);

  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_rotate_square) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure_x = 0;
  model->figure_y = 0;

  const int(*figure)[FIGURE_SIZE] = get_available_figure(3);
  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      model->figure[y][x] = figure[y][x];
    }
  }

  GameInfo_t info = {0};
  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  rotate(model);

  for (int y = 0; y < FIGURE_SIZE; y++) {
    for (int x = 0; x < FIGURE_SIZE; x++) {
      ck_assert_int_eq(model->figure[y][x], figure[y][x]);
    }
  }

  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_rotate_model_null) {
  GameModel_t *model = NULL;
  drop_down(model);
}

START_TEST(test_rotate_model_figure_null) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  model->figure = NULL;
  GameInfo_t info = {0};
  model->info = &info;
  rotate(model);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_rotate_model_info_null) {
  GameModel_t *model = get_current_model();
  model->state = GS_Moving;
  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->info = NULL;
  rotate(model);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  ck_assert_ptr_null(model->info);
}

Suite *rotate_siute() {
  Suite *s = suite_create("move_rotate");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_rotate_ok);
  tcase_add_test(tc_core, test_rotate_collision);
  tcase_add_test(tc_core, test_rotate_square);
  tcase_add_test(tc_core, test_rotate_model_null);
  tcase_add_test(tc_core, test_rotate_model_figure_null);
  tcase_add_test(tc_core, test_rotate_model_info_null);

  suite_add_tcase(s, tc_core);
  return s;
}
