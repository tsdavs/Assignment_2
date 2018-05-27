/**
 * Projectiles
 */
#ifndef _PROJECTILE_HPP_INCLUDED_
#define _PROJECTILE_HPP_INCLUDED_

#include "euclidean2/math/vec3.hpp"

//extern 

static constexpr float GRAVITY = -9.8f;

struct projectile_t
{
	vec3_t     position;
	vec3_t     velocity;	

    material_t mat;
};

/**
 *	Create a projectile
 */
void projectile_create(float x, float y, float z, float pitch, float yaw, float power);
void projectile_create(float x, float y, float z, float pitch, float vx, float vz, float power);

/**
 * Update a projectile
 */
void projectile_update(float dt);

/**
 * Draw a projectile
 */
void projectile_draw();


















#endif
