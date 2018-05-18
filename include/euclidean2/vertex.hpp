/**
 *  Vertex struct
 */
#ifndef _VERTEX_HPP_INCLUDED
#define _VERTEX_HPP_INCLUDED_

#include "euclidean2/math/vec3.hpp"
#include "euclidean2/vecd.hpp"

/**
 *  3D vertex data structure
 */
struct vertex3f_t
{
    vec3_t position;   /**< This vertex's position in 3D space */
    vec3_t  normal;     /**< This vertex's normal vector */
    vec3_t  tangent;    /**< This vertex's tangent vector */
    vec3_t  binormal;   /**< This vertex's binormal vector */
    vec2f_t uv;         /**< This vertex's UV co-ords */
};


#endif
