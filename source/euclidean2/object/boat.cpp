/**
 *	Implementation of boat.hpp
 */
#include "euclidean2/object/boat.hpp"
#include "euclidean2/object/water.hpp"
#include "euclidean2/math/e_math.hpp"
//#include "euclidean2/math/angle.hpp"
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
float angle;

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
	//angle = v_Angle(boat.normal, v1.normal);
	printf("%f\t%f\t%f\n",v1.normal.i, v1.normal.j, v1.normal.k);

	//for some reason this only works if x is 90???
	glRotatef(v1.normal.j, v1.normal.j, v1.normal.k, 1.0f);

	material_bind(b.mat);
	glutSolidTeapot(0.2f);

	
	//v_Draw(boat.position, v1.normal);
	//v_Draw(boat.position, boat.normal);


	glPopMatrix();

}

void boat_animate(boat_t& b, float t, int numWaves)
{
    float wave = 0.0f;
    //float dydx = 0.0f;
    //float dydz = 0.0f;

	for(int n = 0; n < numWaves; n++)
	{
		wave += m_calculateSine(a[n], kx[n], kz[n], w[n], b.x, b.z, t);
		//dydx += m_calcDYDX(a[n], kx[n], kz[n], b.x, b.z, w[n], t);
        //dydz += m_calcDYDZ(a[n], kx[n], kz[n], b.x, b.z, w[n], t);
	}

    /*boat.normal.i = -dydx;
    boat.normal.j = 1.0f;
    boat.normal.k = -dydz;
    v_Normalize(boat.normal);  
*/

	b.y = wave;
	wave = 0.0f;
	//dydx = 0.0f;
    //dydz = 0.0f;


}

