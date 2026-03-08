#ifndef _S21_UTILS_TESTS_H_
#define _S21_UTILS_TESTS_H_

#include <check.h>
#include <unistd.h>

#include "../../inc/backend/utils.h"

Suite *create_matrix_suite();
Suite *remove_matrix_suite();
Suite *get_current_time_suite();
Suite *is_time_suite();

#endif