/**
 *  Functions to load and manipulate textures 
 */
#ifndef _TEXTURE_HPP_INCLUDED_
#define _TEXTURE_HPP_INCLUDED_

#include "platform.hpp"
#include <stdint.h>

/**
 *  Our logical texture
 */
struct texture_t
{
    GLuint      texID;      /**< Our texture's ID (for OpenGL) */
    int         width;      /**< Texture width */
    int         height;     /**< Texture height */

    uint8_t*    texDat; 
};

/**
 *  Load a texture from disk.
 */
bool texture_load(texture_t& tex, const char* path);

/**
 *  Bind a texture for draw calls.
 */
void texture_bind(texture_t& tex);

/**
 *  Unbind textures from GL_TEXTURE_2D
 */
void texture_unbind();

#endif

