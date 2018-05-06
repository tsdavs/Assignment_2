/**
 *  OpenGL helper functions
 */
#ifndef _GL_HELPER_H_INCLUDED
#define _GL_HELPER_H_INCLUDED

#include "platform.hpp"

#include <cstdio>

/**
 *  Wrapper to call _and_ log any OpenGL function passed to it. 
 *  Thanks to Yan Chernikov (@ EA) for this one!!!
 *
 *  NOTE: This CANNOT be used after glBegin() under any circumstance. It will generate a GL_INVALID_OPERATION if so
 **/
#define GLCall(f) GLClearError();\
    f;\
    GLLog();\

/**
 *  Clear the current OpenGL error.
 */
static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

/**
 *  If an error occurs, log it.
 */
static void GLLog()
{
    GLenum error;
    
    while((error = glGetError()) != GL_NO_ERROR)
    {
        printf("GL_ERROR: %s\n", gluErrorString(error));
    }
}



#endif

