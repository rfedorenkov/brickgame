#include "../../inc/backend/utils.h"

int** create_matrix(int rows, int columns) {
  int** matrix = NULL;
  if (rows > 0 && columns > 0) {
    matrix = calloc(rows, sizeof(int*));
    if (matrix != NULL) {
      int failed = 0;
      for (int i = 0; i < rows && !failed; i++) {
        matrix[i] = calloc(columns, sizeof(int));
        if (matrix[i] == NULL) {
          failed = 1;
        }
      }
      if (failed) {
        remove_matrix(matrix, rows);
        matrix = NULL;
      }
    }
  }
  return matrix;
}

int** remove_matrix(int** matrix, int size) {
  if (matrix != NULL && size >= 0) {
    for (int i = 0; i < size; i++) {
      free(matrix[i]);
    }
    free(matrix);
    return NULL;
  } else {
    return matrix;
  }
}

long long get_current_time(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

bool is_time(void) {
  bool result = false;
  GameModel_t* model = get_current_model();
  if (model != NULL && model->info != NULL) {
    long long current_time = get_current_time();
    if (current_time - model->last_time >= model->info->speed) {
      result = true;
      model->last_time = current_time;
    }
  }
  return result;
}