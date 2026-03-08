#include <float.h>
#include <math.h>

#include "backend_tests/backend_tests.h"
#include "fsm_tests/fsm_tests.h"
#include "logic_tests/logic_tests.h"
#include "move_tests/move_tests.h"
#include "storage_tests/storage_tests.h"
#include "utils_tests/utils_tests.h"

int main(void) {
  int number_failed = 0;

  Suite *suites[] = {
      // Backend
      init_game_suite(),
      init_game_info_suite(),
      init_fields_suite(),

      // FSM
      update_current_state_suite(),
      is_action_allowed_suite(),
      user_input_suite(),
      is_started_suite(),
      is_paused_suite(),
      is_game_over_suite(),
      is_exit_suite(),
      start_suite(),
      pause_game_suite(),
      game_over_suite(),  // TODO

      // Logic
      lock_figure_suite(),
      remove_lines_on_field_suite(),
      update_score_and_level_suite(),
      check_collision_suite(),
      generate_random_figure_suite(),
      generate_figure_suite(),
      get_current_figure_suite(),
      get_figure_x_suite(),
      get_figure_y_suite(),

      // Move
      move_left_suite(),
      move_right_suite(),
      move_down_suite(),
      drop_down_suite(),
      rotate_siute(),

      // Storage
      load_high_score_file_ok_suite(),
      save_high_score_file_ok_suite(),

      // Utils
      create_matrix_suite(),
      remove_matrix_suite(),
      get_current_time_suite(),
      is_time_suite(),
  };

  for (size_t i = 0; i < sizeof(suites) / sizeof(Suite *); i++) {
    SRunner *sr = srunner_create(suites[i]);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return (number_failed == 0) ? 0 : 1;
}