#include "logic_tests.h"

START_TEST(test_update_score_and_level_one) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 1);
  int exp = 100;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
}

START_TEST(test_update_score_and_level_two) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 2);
  int exp = 300;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
}

START_TEST(test_update_score_and_level_three) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 3);
  int exp = 700;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
}

START_TEST(test_update_score_and_level_four) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 4);
  info.level = MAX_LEVEL;
  int exp = 1500;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
  ck_assert_int_eq(info.level, MAX_LEVEL);
}

START_TEST(test_update_score_and_level_zero) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 0);
  int exp = 0;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
}

START_TEST(test_update_score_and_level_info_null) {
  update_score_and_level(NULL, 0);
}

START_TEST(test_update_score_and_level_five) {
  GameInfo_t info = {0};
  update_score_and_level(&info, 5);
  int exp = 0;
  ck_assert_int_eq(info.score, exp);
  ck_assert_int_eq(info.high_score, exp);
}

Suite *update_score_and_level_suite() {
  Suite *s = suite_create("logic_update_score_and_level");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_update_score_and_level_one);
  tcase_add_test(tc_core, test_update_score_and_level_two);
  tcase_add_test(tc_core, test_update_score_and_level_three);
  tcase_add_test(tc_core, test_update_score_and_level_four);
  tcase_add_test(tc_core, test_update_score_and_level_zero);
  tcase_add_test(tc_core, test_update_score_and_level_info_null);
  tcase_add_test(tc_core, test_update_score_and_level_five);
  suite_add_tcase(s, tc_core);
  return s;
}
