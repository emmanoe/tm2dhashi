#ifndef TEST_TOOLBOX_H
#define TEST_TOOLBOX_H


/**
 * @brief Test if expected == value and return the result. 
 * If the result is false, then it prints msg on the standard error output.
 *
 **/
bool test_equality_int(int expected, int value, char * msg);


/**
 * @brief Test if expected == value and return the result. 
 * If the result is false, then it prints msg on the standard error output.
 *
 **/
bool test_equality_bool(bool expected, bool value, char * msg);


/**
 * @brief Test if  value is in the interval [val_min, val_max] and return the result.
 *  If the result is false, then it prints msg on the standard error output.
 *
 **/bool test_interval_int(int val_min, int val_max, int value, char * msg);
#endif // TEST_TOOLBOX_H
