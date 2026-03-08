#ifndef _S21_STORAGE_TESTS_H_
#define _S21_STORAGE_TESTS_H_

#include <check.h>
#include <sys/stat.h>

#include "../../inc/backend/storage.h"

Suite *load_high_score_file_ok_suite();
Suite *save_high_score_file_ok_suite();

#endif