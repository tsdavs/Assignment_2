/**
 *  Numeric stuff
 */
#ifndef _E_NUMERIC_HPP_INCLUDED
#define _E_NUMERIC_HPP_INCLUDED


#include <algorithm>

/**
 * Clamps a value between lower and upper
 */
template <typename T>
T clamp(const T& n, const T& lower, const T& upper) 
{
  return std::max(lower, std::min(n, upper));
}

#endif