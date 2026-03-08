#include "../../inc/backend/storage.h"

int load_high_score_file(int* high_score) {
  int error = 0;
  if (high_score == NULL) {
    error = -1;
  }
  if (!error) {
    FILE* file = fopen(HIGH_SCORE_FILE, "r");
    if (file != NULL) {
      if (fscanf(file, "%d", high_score) != 1) {
        error = -1;
      }
      fclose(file);
    } else {
      error = -1;
    }
  }
  return error;
}

int save_high_score_file(int high_score) {
  int error = 0;
  FILE* file = fopen(HIGH_SCORE_FILE, "w");
  if (file != NULL) {
    if (fprintf(file, "%d\n", high_score) < 0) {
      error = -1;
    }
    fclose(file);
  } else {
    error = -1;
  }
  return error;
}