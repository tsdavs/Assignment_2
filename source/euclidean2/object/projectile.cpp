/**
 *	Implementation of projectile.hpp
 */
#include "euclidean2/object/projectile.hpp"
#include "euclidean2/math/angle.hpp"
#include "platform.hpp"

#include <vector>



// TODO: Projectile list here

std::vector<projectile_t> active_list;

void projectile_create(float x, float y, float z, float pitch, float yaw)
{
	projectile_t p;
	
	p.position.x = x;
	p.position.y = y;
	p.position.z = z;

	p.velocity.x = sinf(pitch) * cosf(yaw);
	p.velocity.y = cosf(pitch);
	p.velocity.z = sinf(pitch) * sinf(yaw);

	active_list.push_back(p);
}

void projectile_draw(projectile_t& proj)
{
	for(int i = 0; i < active_list.size(); i++)
	{
		glPushMatrix();
		glTranslatef(proj.position.x, proj.position.y, proj.position.z);
		glutSolidSphere(0.3f, 20, 20);
		glPopMatrix();
	}
}

void projectile_update(projectile_t& proj)
{
	// TODO: If projectile y == 0, cull this projectile

	for(int i = 0; i < active_list.size(); i++)
	{
		
	}
}
