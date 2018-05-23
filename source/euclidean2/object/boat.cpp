/**
 *	Implementation of boat.hpp
 */
#include "euclidean2/object/boat.hpp"
#include "euclidean2/object/water.hpp"
#include "euclidean2/math/e_math.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/math/vec3.hpp"

#include <vector>

extern float m_calculateSine(float a, float kx, float kz, float w, float x, float z, float t);
extern float m_calcDYDX(float a, float kx, float kz, float x, float z, float w, float t);
extern float m_calcDYDZ(float a, float kx, float kz, float x, float z, float w, float t);

extern float a[];
extern float kx[]; 
extern float kz[];
extern float w[];

extern vertex3f_t v1;

void boat_spawn(boat_t& b, float x, float y, float z)
{
	b.position.x = x;
	b.position.y = y;
	b.position.z = z;

	b.position.i = -b.position.x;
	b.position.j = -b.position.y;
	b.position.k = -b.position.z;

    b.stopping_pos = (static_cast<float>(rand())/(static_cast<float>(RAND_MAX)/10.f))+2.0f;

	b.mag = v_Magnitude(b.position);

	material_create(b.mat, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f);
}

void boat_draw(boat_t& b)
{
	glPushMatrix();
	glTranslatef(b.position.x, b.position.y, b.position.z);

	glRotatef(ANG_2_DEGREES(v1.normal.i), ANG_2_DEGREES(v1.normal.j), ANG_2_DEGREES(v1.normal.k),1.0f);

	material_bind(b.mat);
	glutSolidTeapot(0.2f);

	glPopMatrix();
}

void boat_animate(boat_t& b, float t, int numWaves)
{
    float wave = 0.0f;

    float pos = sqrt(b.position.x*b.position.x + b.position.z*b.position.z);

    if(pos >= b.stopping_pos)
    {
    	b.position.x += (b.position.i/b.mag) * t/500.0f; 
    	b.position.z += (b.position.k/b.mag) * t/500.0f; 
    }
    else
    {
    	//x=cos(angle) * b.stopping_pos
    	//z=sin(angle) * b.stopping_pos
    }

	for(int n = 0; n < numWaves; n++)
	{
		wave += m_calculateSine(a[n], kx[n], kz[n], w[n], b.position.x, b.position.z, t);
	}

	b.position.y = wave;
	wave = 0.0f;
}

void boat_shoot(boat_t& b, float t)
{
	
}


