#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_toolbox.h"


bool test_equality_int(int expected, int value, char * msg) {
  if (expected != value) {
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return false;
  }
  return true;
}

bool test_interval_int(int val_min, int val_max, int value, char * msg) {
  if (value < val_min  || val_max < value) {
    fprintf(stderr,"ERR: interval expected [%d,%d] ; value computed %d. %s\n", val_min, val_max, value, msg);
    return false;
  }
  return true;
}



bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value) {
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return false;
  }
  return true;
}
