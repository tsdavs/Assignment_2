/**
 *  Light data structure and functions
 */
#ifndef _LIGHT_HPP_INCLUDED
#define _LIGHT_HPP_INCLUDED

#include "euclidean2/vecd.hpp"
#include "platform.hpp"

struct light_t
{
    vec4f_t position;
    vec4f_t color; 

    GLenum  lightnum = 0;
};

/**
 *  Create a light
 */
void light_create(light_t& light, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, GLfloat positional, GLfloat l_attenuation, GLfloat q_atenuation, GLenum lightnum);

/**
 *  Enable a light for use
 */
void light_enable(light_t& light);

/**
 *  Disable a light source
 */
void light_disable(light_t& light);

/**
 *	Draw a light on screen
 */
void light_draw(light_t& light);

/**
 * Get the number of active lights
 */
int light_getActiveLightCount(void);

/**
 *	Translate a light source
 */	
void light_translate(light_t& light, GLfloat dx, GLfloat dy, GLfloat dz);


#endif
