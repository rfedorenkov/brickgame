#include "fsm_tests.h"

START_TEST(test_pause_game_playing) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Moving;
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 1);
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 0);
}

START_TEST(test_pause_game_stopped) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Exit;
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 1);
}

START_TEST(test_pause_game_not_started) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Start;
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 0);
}

START_TEST(test_pause_game_over) {
  GameModel_t *model = get_current_model();
  GameInfo_t info = {0};
  model->info = &info;
  model->state = GS_Over;
  pause_game(&info, model->state);
  ck_assert_int_eq(is_paused(), 0);
}

Suite *pause_game_suite() {
  Suite *s = suite_create("fsm_pause_game");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_pause_game_playing);
  tcase_add_test(tc_core, test_pause_game_stopped);
  tcase_add_test(tc_core, test_pause_game_not_started);
  tcase_add_test(tc_core, test_pause_game_over);
  suite_add_tcase(s, tc_core);
  return s;
}