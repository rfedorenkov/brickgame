#include "backend_tests.h"

START_TEST(test_init_game_info) {
  GameInfo_t info = {0};
  info.score = -99;
  info.level = -99;
  info.speed = -99;
  info.pause = -99;

  int high_score = 0;
  load_high_score_file(&high_score);
  remove(HIGH_SCORE_FILE);

  init_game_info(&info);
  ck_assert_int_eq(info.score, 0);
  ck_assert_int_eq(info.level, MIN_LEVEL);
  ck_assert_int_eq(info.speed, START_SPEED);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.high_score, 0);
  save_high_score_file(high_score);
}

START_TEST(test_init_game_info_null) { init_game_info(NULL); }

Suite *init_game_info_suite() {
  Suite *s = suite_create("backend_init_fields");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_game_info);
  tcase_add_test(tc_core, test_init_game_info_null);
  suite_add_tcase(s, tc_core);
  return s;
}