#ifndef _S21_FSM_TESTS_H_
#define _S21_FSM_TESTS_H_

#include <check.h>

#include "../../inc/backend/fsm.h"

Suite *update_current_state_suite();
Suite *is_action_allowed_suite();
Suite *user_input_suite();

Suite *is_started_suite();
Suite *is_paused_suite();
Suite *is_game_over_suite();
Suite *is_exit_suite();

Suite *start_suite();
Suite *pause_game_suite();
Suite *game_over_suite();

#endif