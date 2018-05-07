/**
 *  2D Vector related structures and functions
 */
#ifndef _VEC2_INCLUDED_H
#define _VEC2_INCLUDED_H

#include <cstdio>

/**
 *  Our vec2 class. We're using 'traditional' mathematical notation of i and j for this.
 */
struct vec2_t
{
    float i;    /**< Length along the x axis */
    float j;    /**< Length along the y axis */

    float x;    /**< Position of this vector on the x axis */ 
    float y;    /**< Position of this vector on the y axis */

    /**
     *  NOTE: g++ with -Weffc++ tells us we should return by value for these!!??!?
     */

    /**
     *  Vector addition operator. Adds this vector to 'rhs' and returns a new vector
     */
    vec2_t operator+(const vec2_t& rhs);

    /**
     *  Adds vector 'rhs' to this
     */
    vec2_t& operator+=(const vec2_t& rhs);

    /**
     *  Vector subtraction operator. Subtracts this vector to 'rhs' and returns this vec3_t
     */

    /**
     *  Scale this vector by an scalar, 'rhs'
     */
    vec2_t operator*(const float rhs);
    vec2_t& operator*=(const float rhs);

    void print(void)
    {
        std::printf("x: %f, y: %f\ni: %f, j: %f\n", x, y, i, j);
    }
};

/**
 *  Get the dot product of this vector
 */
float v_Dot(vec2_t& vec1, vec2_t& vec2);

/**
 *  Normalizes a vector
 *
 *  @param vec @ref t that we want to normalize
 */
void v_Normalize(vec2_t& vec);

/**
 *  Get the magnitude of a t
 *
 *  @param vec Vector whose magnitude we want to calculate
 */
float v_GetMagnitude(vec2_t& vec);

/**
 *  Get the angle this vector makes with the x-axis
 *
 *  @param vec Vector whose angle we want to calculate
 */
float v_GetAngle(vec2_t& vec);

/**
 *  Draw this vector to the screen
 *
 *  @param vec Vector we want to draw
 */
void v_Draw(vec2_t& vec, float r, float g, float b, float s, bool normalize);


#endif
