#ifndef _TRIGMATH_H_
#define _TRIGMATH_H_
#include <math.h>

//! C wrapper for our C++ functions
/** Modified Math.h to include sin, cos, and tan **/

float my_sin(float x);

float my_cos(float x);

float my_atan(float x);

float my_atan2(float y, float x);

float prand(unsigned int * x);

#endif
