/**
 *	Boat related stuff.
 */
#ifndef _BOAT_HPP_INCLUDED_
#define _BOAT_HPP_INCLUDED_

#include "euclidean2/system/material.hpp"

struct boat_t
{
	float 		x;		/**< Boat x position */
	float 		y;		/**< Boat y position */
	float 		z;		/**< Boat z position */

	material_t 	mat; 	/**< Boat material */
};

void boat_spawn(boat_t& b, float x, float y, float z);

void boat_draw(boat_t& b);






#endif
