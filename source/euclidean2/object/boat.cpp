/**
 *	Implementation of boat.hpp
 */
#include "euclidean2/object/boat.hpp"

#include <vector> 

void boat_spawn(boat_t& b, float x, float y, float z)
{
	b.x = x;
	b.y = y;
	b.z = z;

	material_create(b.mat, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f);
}

void boat_draw(boat_t& b)
{
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(b.x, b.y, b.z);
	material_bind(b.mat);
	glutSolidTeapot(0.2f);
	glPopMatrix();
}
