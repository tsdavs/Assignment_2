/**
 *  3 dimensional vector related functions and structures.
 */
#ifndef _VEC3_H_INCLUDED
#define _VEC3_H_INCLUDED

#include <cstdio>

/**
 *  Our standard vec3 structure. We use the mathematical notation i, j, k for the length, and x, y, z for the position
 */
struct vec3_t final
{
    float x;    /**< Vector x position */
    float y;    /**< Vector y position */
    float z;    /**< Vector z position */

    float i;    /**< Length along x-axis */
    float j;    /**< Length along y-axis */
    float k;    /**< Length along z-axis */

    /**
     *  NOTE: g++ with -Weffc++ tells us we should return by value for these!!??!?
     */

    /**
     *  Vector addition operator. Adds this vector to 'rhs' and returns a new vector
     */
    vec3_t operator+(const vec3_t& rhs);

    /**
     *  Adds vector 'rhs' to this
     */
    vec3_t& operator+=(const vec3_t& rhs);

    /**
     *  Vector subtraction operator. Subtracts this vector to 'rhs' and returns this vec3_t
     */

    /**
     *  Scale this vector by an scalar, 'rhs'
     */
    vec3_t operator*(const float rhs);
    vec3_t& operator*=(const float rhs);

    void print(void)
    {
        std::printf("x: %f, y: %f, z: %f\ni: %f, j: %f, k: %f\n", x, y, z, i, j, k);
    }

};

/**
 *  Magnitude of vector
 */
float v_Magnitude(vec3_t& vec);

/**
 *  Normalize a vector
 */
void v_Normalize(vec3_t& vec);

/**
 *  Calculate the dot product of two 3D vectors
 */
float v_Dot(vec3_t& vec1, vec3_t& vec2);

/**
 *  Vector cross product
 *
 *  Returns a full object; a necessary evil unfortunately.
 */
vec3_t v_Cross(vec3_t& vec1, vec3_t& vec2);

/**
 *  Find the angle between two vectors
 */
float v_Angle(vec3_t& vec1, vec3_t& vec2);

/**
 *  Get the pitch of the vector
 */
float v_GetPitch(vec3_t& vec);

/**
 *  Get the pitch of this vector
 */
float v_GetYaw(vec3_t& vec);







#endif
