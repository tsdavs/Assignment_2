/**
 *	Implementation of boat.hpp
 */
#include "euclidean2/object/boat.hpp"
#include "euclidean2/object/water.hpp"
#include "euclidean2/math/e_math.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/math/vec3.hpp"
//#include "euclidean2/math/vec2.hpp"

#include <vector>

extern float m_calculateSine(float a, float kx, float kz, float w, float x, float z, float t);
extern float m_calcDYDX(float a, float kx, float kz, float x, float z, float w, float t);
extern float m_calcDYDZ(float a, float kx, float kz, float x, float z, float w, float t);

extern float a[];
extern float kx[]; 
extern float kz[];
extern float w[];

extern vertex3f_t v1;

vertex3f_t boat;

void boat_spawn(boat_t& b, float x, float y, float z)
{
	boat.position.x = x;
	boat.position.y = y;
	boat.position.z = z;


	material_create(b.mat, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f);
}

void boat_draw(boat_t& b)
{
	glPushMatrix();
	glTranslatef(b.x, b.y, b.z);

	glRotatef(ANG_2_DEGREES(v1.normal.i), ANG_2_DEGREES(v1.normal.j), ANG_2_DEGREES(v1.normal.k),1.0f);

	material_bind(b.mat);
	glutSolidTeapot(0.2f);

	glPopMatrix();

}

void boat_animate(boat_t& b, float t, int numWaves)
{
    float wave = 0.0f;

	for(int n = 0; n < numWaves; n++)
	{
		wave += m_calculateSine(a[n], kx[n], kz[n], w[n], b.x, b.z, t);
	}

	b.y = wave;
	wave = 0.0f;
}

