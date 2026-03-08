#ifndef _S21_MOVE_TESTS_H_
#define _S21_MOVE_TESTS_H_

#include <check.h>
#include <sys/stat.h>

#include "../../inc/backend/fsm.h"
#include "../../inc/backend/move.h"

Suite *move_left_suite();
Suite *move_right_suite();
Suite *move_down_suite();
Suite *drop_down_suite();
Suite *rotate_siute();

#endif