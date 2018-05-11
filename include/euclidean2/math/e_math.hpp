/**
 *  Math related header file
 */
#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <cstdlib>


float q_rsqrt(float number);

static inline float e_random()
{
	float ret;

	ret = static_cast<float>((rand()) + 1) / static_cast<float>(RAND_MAX);
	
	return ret;
}

#endif
