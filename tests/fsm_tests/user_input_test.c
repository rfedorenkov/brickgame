#include "fsm_tests.h"

START_TEST(test_user_input_start) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  userInput(Start, false);
  ck_assert_int_eq(model->state, GS_Spawn);
  ck_assert_int_eq(is_started(), 1);
}

START_TEST(test_user_input_terminate) {
  GameModel_t *model = get_current_model();
  userInput(Terminate, false);
  ck_assert_int_eq(model->state, GS_Exit);
}

START_TEST(test_user_input_pause) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Moving;
  userInput(Pause, false);
  ck_assert_int_eq(is_paused(), 1);
}

START_TEST(test_user_input_left) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->figure_x = 5;
  model->state = GS_Moving;
  userInput(Left, true);
  ck_assert_int_eq(model->figure_x, 4);
}

START_TEST(test_user_input_right) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->figure_x = 5;
  model->state = GS_Moving;
  userInput(Right, true);
  ck_assert_int_eq(model->figure_x, 6);
}

START_TEST(test_user_input_down) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};

  model->info = &info;
  info.field = create_matrix(FIELD_HEIGHT, FIELD_WIDTH);

  model->state = GS_Moving;
  int exp = FIELD_HEIGHT - 1;

  model->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
  model->figure[0][0] = 1;

  userInput(Down, true);
  ck_assert_int_eq(model->figure_y, exp);
  model->figure = remove_matrix(model->figure, FIGURE_SIZE);
  ck_assert_ptr_null(model->figure);
  info.field = remove_matrix(info.field, FIELD_HEIGHT);
  ck_assert_ptr_null(model->figure);
}

START_TEST(test_user_input_action) {
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

  userInput(Action, false);

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

START_TEST(test_user_input_left_paused) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->state = GS_Moving;
  model->info = &info;
  int exp = 5;
  model->figure_x = exp;
  pause_game(&info, model->state);
  userInput(Left, true);
  ck_assert_int_eq(model->figure_x, exp);
}

START_TEST(test_user_input_left_not_started) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->state = GS_Start;
  model->info = &info;
  int exp = 5;
  model->figure_x = exp;
  userInput(Left, true);
  ck_assert_int_eq(model->figure_x, exp);
}

START_TEST(test_user_input_up) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  int exp = 5;
  model->figure_y = exp;
  model->state = GS_Moving;
  userInput(Up, true);
  ck_assert_int_eq(model->figure_y, exp);
}

Suite *user_input_suite() {
  Suite *s = suite_create("fsm_user_input");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_user_input_start);
  tcase_add_test(tc_core, test_user_input_terminate);
  tcase_add_test(tc_core, test_user_input_pause);
  tcase_add_test(tc_core, test_user_input_left);
  tcase_add_test(tc_core, test_user_input_right);
  tcase_add_test(tc_core, test_user_input_down);
  tcase_add_test(tc_core, test_user_input_action);
  tcase_add_test(tc_core, test_user_input_left_paused);
  tcase_add_test(tc_core, test_user_input_left_not_started);
  tcase_add_test(tc_core, test_user_input_up);
  suite_add_tcase(s, tc_core);
  return s;
}