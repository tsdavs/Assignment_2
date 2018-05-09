/**
 *  Pure data vectors
 */
#ifndef _VECD_HPP_INCLUDED_
#define _VECD_HPP_INCLUDED_

#include "platform.hpp"

/**
 *  Pure data 2d vector
 */
struct __attribute__((packed)) vec2_data_t
{
    GLfloat x;
    GLfloat y;
};

struct __attribute__((packed)) vec3_data_t
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct __attribute__((packed)) vec4f_t
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};


#endif