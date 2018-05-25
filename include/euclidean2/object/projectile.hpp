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
	vec3_t position;
	vec3_t velocity;	
};

/**
 *	Create a projectile
 */
void projectile_create(float x, float y, float z, float pitch, float yaw);

/**
 * Update a projectile
 */
void projectile_update(projectile_t& proj);

/**
 * Draw a projectile
 */
void projectile_draw(projectile_t& proj);


















#endif
