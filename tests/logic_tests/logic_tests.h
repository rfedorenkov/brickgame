#ifndef _S21_LOGIC_TESTS_H_
#define _S21_LOGIC_TESTS_H_

#include <check.h>

#include "../../inc/backend/logic.h"

Suite *lock_figure_suite();
Suite *remove_lines_on_field_suite();
Suite *update_score_and_level_suite();
Suite *check_collision_suite();
Suite *generate_random_figure_suite();
Suite *generate_figure_suite();
Suite *get_current_figure_suite();
Suite *get_figure_x_suite();
Suite *get_figure_y_suite();

#endif