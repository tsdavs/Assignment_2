/**
 *  Implementation of e_math.h
 */
#include "euclidean2/math/e_math.hpp"

#include <cstdint>

/**
 *  Fast square root based on the initial version devised by Gary Tarolli at SGI/3Dfx
 *  and made famous by John Carmack in Quake III. 
 *
 *  Works by performing two fast iterations of Newton's method (yn - (f(yn)/f'(yn)))
 *  
 *  Code for this can be found here (with a relevant explanation):
 *
 *  This is being used because we aren't using any compiler optimisations (i.e SSE) to speed up calculations a bit.
 *  Returns 1/sqrt of the value passed to it. We can use to quickly work out the calculation.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast" // We need the old style cast for this, it doesn't translate too well to c++...
float q_rsqrt(float number)
{
    uint32_t i; // Ensure that we are using a 32-bit integer, as 64-bits will mess up the result.
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(uint32_t*)&y;         // Evil 32-bit float bit hacking
    i = 0x5F375A86 - (i >> 1);  // Hahaha, what the fuck?!
    y = *(float*)&i;
    
    y = y * (threehalfs - (x2 * y * y)); // First iteration of Newton's method

    return y;
}

#pragma GCC diagnostic pop
