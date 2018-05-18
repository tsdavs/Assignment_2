/**
 *  Implementation of light.cpp
 */
#include "euclidean2/system/light.hpp"
#include "euclidean2/math/angle.hpp"

#include <cstdio>

static GLfloat col_amb[] = {1.0f, 1.0f, 1.0f, 1.0f};
static GLfloat col_spc[] = {1.0f, 1.0f, 1.0f, 1.0f};


static int numActiveLights = 0;

void light_create(light_t& light, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z, GLfloat positional, GLfloat l_attenuation, GLfloat q_attenuation, GLenum lightnum)
{
    if(lightnum > GL_LIGHT7)
    {
        fprintf(stderr, "error: Invalid light number %d!\n", lightnum);
        return;
    }

    light.color.x       = r;
    light.color.y       = g;
    light.color.z       = b;
    light.color.w       = 1.0f;

    light.position.x    = x;
    light.position.y    = y;
    light.position.z    = z;
    light.position.w    = positional;

    light.lightnum      = lightnum;

    glEnable(lightnum);

    glLightfv(lightnum, GL_POSITION, reinterpret_cast<float*>(&light.position));
	glLightfv(lightnum, GL_AMBIENT, col_amb);
    glLightfv(lightnum, GL_DIFFUSE, reinterpret_cast<float*>(&light.color));
	glLightfv(lightnum, GL_SPECULAR, col_spc);
    glDisable(lightnum);
}

void light_enable(light_t& light)
{
    if(light.lightnum == 0)
    {
        fprintf(stderr, "error: Invalid light number %d! Did you create a light?!?!\n", light.lightnum);
        return;
    }

	glEnable(light.lightnum);
	glLightfv(light.lightnum, GL_POSITION, reinterpret_cast<float*>(&light.position));

	numActiveLights++;
}

void light_disable(light_t& light)
{
    if(light.lightnum == 0)
    {
        fprintf(stderr, "error: Invalid light number %d! Did you create a light?!?!\n", light.lightnum);
        return;
    }

    glDisable(light.lightnum);

	numActiveLights--;
}

void light_draw(light_t& light)
{
	glDisable(GL_LIGHTING); // Dont' apply lighting to the lights (hahahahaha)

	glColor3f(1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(light.position.x, light.position.y, light.position.z);
	glutSolidCube(0.05f);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void light_translate(light_t& light, float dx, float dy, float dz)
{
	light.position.x += dx;
	light.position.y += dy;
	light.position.z += dz;
}

int light_getActiveLightCount(void)
{
	return numActiveLights;
}
