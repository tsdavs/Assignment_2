/**
 *	Boat related stuff.
 */
#ifndef _BOAT_HPP_INCLUDED_
#define _BOAT_HPP_INCLUDED_

#include "euclidean2/system/material.hpp"
#include "euclidean2/math/vec3.hpp"

struct boat_t
{
	vec3_t position;	/**< Boat vector */
	material_t 	mat; 		/**< Boat material */
	float mag;
	float stopping_pos;

};

void boat_spawn(boat_t& b, float x, float y, float z);

void boat_draw(boat_t& b);

void boat_animate(boat_t& b, float t, int numWaves);


struct island_t
{
	vec3_t position;	/**< Boat vector */
	material_t 	mat; 		/**< Boat material */
};


#endif

