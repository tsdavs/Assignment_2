/**
 *  Implementation of texture.hpp
 */
#include "euclidean2/system/texture.hpp"

#include <cstdio>
#include <cstdlib>
#include "SOIL.h"

bool texture_load(texture_t& tex, const char* path)
{
    //tex.texID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    tex.texID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if(tex.texID == 0)
    {
        printf("%s:%d tex.texID == 0!\n", __PRETTY_FUNCTION__, __LINE__);
        abort();
    }

    glBindTexture(GL_TEXTURE_2D, tex.texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // Texture wrap for 'v' co-ords
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    // Texture wrap for 'u' co-ords
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void texture_bind(texture_t& tex)
{
    glBindTexture(GL_TEXTURE_2D, tex.texID); 
}

void texture_unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

