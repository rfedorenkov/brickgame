#ifndef _S21_BACKEND_TESTS_H_
#define _S21_BACKEND_TESTS_H_

#include <check.h>

#include "../../inc/backend/backend.h"
#include "../../inc/backend/fsm.h"

Suite *init_game_suite();
Suite *init_game_info_suite();
Suite *init_fields_suite();

#endif