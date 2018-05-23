/**
 *
 */
#include "euclidean2/system/skybox.hpp"
#include "euclidean2/system/texture.hpp"
#include "platform.hpp"
#include "SOIL.h"

#include <cstdio>
#include <string>

static texture_t texID[6];
static const char* names[6] = {"yp.tga", "zn.tga", "zp.tga", "xp.tga", "xn.tga", "yn.tga"};

static constexpr GLfloat width  = 20.0f;
static constexpr GLfloat height = 20.0f;
static constexpr GLfloat length = 20.0f;

void skybox_init()
{
    for(int i = 0; i < 6; i++)
    {
        std::string path = "res/";
        path += names[i];
        texture_load(texID[i], path.c_str());
        path = "res/";
    }
}

// Oh my fucking god, what the fuck is this...
void skybox_draw()
{
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f); // Don't let a glColor** call interfere with our textures!

    texture_bind(texID[0]);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0f, 0.0f); 
    glVertex3f(width, height, -length);
    glTexCoord2d(1.0f, 1.0f); 
    glVertex3f(-width, height, -length);
    glTexCoord2d(0.0, 1.0f); 
    glVertex3f(-width, height, length);
    glTexCoord2d(0.0, 0.0f); 
    glVertex3f( width, height, length);
    glEnd();

    texture_bind(texID[1]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0f, 0.0f); 
    glVertex3f(width, height, length);
    glTexCoord2d(1.0f, 0.0f); 
    glVertex3f(-width, height, length);
    glTexCoord2d(1.0f, 1.0f); 
    glVertex3f(-width, -height, length);
    glTexCoord2d(0.0f, 1.0f); 
    glVertex3f( width, -height, length);
    glEnd();

    texture_bind(texID[2]);
    glPushMatrix();
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, length * 2);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0f, 1.0f); 
    glVertex3f(width, -height, -length);
    glTexCoord2d(1.0f, 1.0f); 
    glVertex3f(-width, -height, -length);
    glTexCoord2d(1.0f, 0.0f); 
    glVertex3f(-width, height, -length);
    glTexCoord2d(0.0f, 0.0f); 
    glVertex3f( width, height, -length);
    glEnd();
    glPopMatrix();

    texture_bind(texID[3]);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0f, 0.0f); 
    glVertex3f(-width, height, -length);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(-width, -height, -length);
    glTexCoord2d(0.0f, 1.0f); 
    glVertex3f(-width, -height, length);
    glTexCoord2d(0.0f, 0.0f); 
    glVertex3f(-width, height, length);
    glEnd();

    texture_bind(texID[4]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0f, 0.0f); 
    glVertex3f(width, height, -length);
    glTexCoord2d(1.0f, 0.0f); 
    glVertex3f(width, height, length);
    glTexCoord2d(1.0f, 1.0f); 
    glVertex3f(width, -height, length);
    glTexCoord2d(0.0f, 1.0f); 
    glVertex3f(width, -height, -length);
    glEnd(); 

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}

