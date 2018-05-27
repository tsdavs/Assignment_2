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

extern std::vector<boat_t> boats;

static constexpr int BOAT_FIRE_DELAY = 20.0f;

void boat_spawn(boat_t& b, float x, float y, float z)
{
	b.position.x = x;
	b.position.y = y;
	b.position.z = z;

	b.position.i = b.position.x;
	b.position.j = 0.0f;
	b.position.k = b.position.z;

    b.velocity.x = 1.0f;
    b.velocity.z = 1.0f;

    b.xRot = 0.0f;
    b.zRot = 0.0f;

    b.stopping_pos = (static_cast<float>(rand())/(static_cast<float>(RAND_MAX)/10.f))+2.0f;

	b.mag = v_Magnitude(b.position);

    b.delayTime = BOAT_FIRE_DELAY;

	material_create(b.mat, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f);
}

void boat_draw(boat_t& b)
{
	glPushMatrix();
	glTranslatef(b.position.x, b.position.y, b.position.z);

	material_bind(b.mat);
	glutSolidCube(0.2f);

	glPopMatrix();
}

void boat_update(boat_t& b, float t, float dt, int numWaves)
{
    float wave = 0.0f;
    float dydx;
    float dydz;

	for(int n = 0; n < numWaves; n++)
	{
		wave += m_calculateSine(a[n], kx[n], kz[n], w[n], b.position.x, b.position.z, t);
        dydx += m_calcDYDX(a[n], kx[n], kz[n], w[n], b.position.x, b.position.z, t);
        dydz += m_calcDYDZ(a[n], kx[n], kz[n], w[n], b.position.x, b.position.z, t);
	}

    float theta = ARTAN(b.position.z/b.position.x);

    b.heading = theta;

    b.dydx = dydx;
    b.dydz = dydz;

    b.xRot = COS(dydx) * dt;
    b.zRot = COS(dydz) * dt;

    b.position.y = wave + 0.1f;

    float distance = v_Magnitude(b.position);

    /**
        Doesn't quite work right...
    // Remove the sign bit from the float 
    uint32_t xAbs = static_cast<uint32_t>(b.position.x) & 0x7fffffff;
    uint32_t zAbs = static_cast<uint32_t>(b.position.z) & 0x7fffffff;

    float xAbsF = static_cast<float>(xAbs);
    float zAbsF = static_cast<float>(zAbs);

    float distance = sqrtf(pow(xAbsF - 1.2f, 2) + pow(zAbsF - 1.2f, 2));
    **/

    b.delayTime -= 0.22f;

    if(distance <= 4.7f)
    {
        b.heading = ANG_2_DEGREES(theta);
        if(b.delayTime <= 0.0f)
        {
            boat_shoot(b);
            b.delayTime = BOAT_FIRE_DELAY;
        }
        return ;
    }

    // This acts _kinda_ strange, but it's actually kinda fun
    // The boats slow down as they come in, which presents a pretty fun
    // challenge. It's not like this is a really big hack or anything!
    // (yes James, I'm looking at you :] )
    b.velocity.z = -b.position.x * TAN(theta) * dt * 0.2f;
    b.velocity.x = -b.position.z / TAN(theta) * dt * 0.2f;

    b.position.x += b.velocity.x * 0.4f;
    b.position.z += b.velocity.z * 0.4f;
    b.position.i += b.velocity.x * 0.4f;
    b.position.k += b.velocity.z * 0.4f;
}

void boat_shoot(boat_t& b)
{
    float vz;
    float vx;

    /**
     *  Don't ask how this works.. Seriously...
     *  tan(90) == tan(270) which is UNDEFINED!
     *  Seriously, it's a division by zero... How this works is beyond me...
     */
    if(b.position.x < 0.0f)
    {
        vx = b.position.x / TAN(270.0f) * 0.1f;
    }
    else
    {
        vx = b.position.x / TAN(90.0f) * 1.1f;
    }

    if(b.position.z < 0.0f)
    {
        vz = b.position.z / TAN(270.0f) * 0.1f;
    }
    else
    {
        vz = b.position.z / TAN(90.0f) * 1.1f;
    }

    projectile_create(b.position.x, b.position.y + 0.2f, b.position.z, 35.0f, vx, vz, 4.5f);
}


