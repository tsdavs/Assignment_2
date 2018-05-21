/**
 *  
 */
#ifndef _WATER_HPP_INCLUDED_
#define _WATER_HPP_INCLUDED_

#include "euclidean2/vertex.hpp"
#include "euclidean2/system/material.hpp"
#include "euclidean2/system/texture.hpp"

#include <climits>
#include <vector>

static constexpr int MIN_TESSELATIONS = 16;
static constexpr int MAX_TESSELATIONS = 512;

struct water_t
{
    int         tesselations = MIN_TESSELATIONS;
    vertex3f_t  verts[MAX_TESSELATIONS][MAX_TESSELATIONS];
    material_t  mat;
};

struct ground_t
{
    vertex3f_t  verts[128][128]; // We don't need too many tesselations for the seafloor
    texture_t   tex;
    material_t  mat;
};

/**
 *  Generate our water using triangle strips
 */
void water_generate(water_t& water);

/**
 *  Actually draw the quad strip
 */
void water_draw(water_t& water, bool drawNorms);

/**
 * Animate our water
 */
void water_animate(water_t& water, float t, int numWaves);

/**
 *  Draw the seafloor
 */
void water_drawGround(ground_t& ground);

/**
 * 
 */
static inline void water_increaseTesselations(water_t& water)
{
    if(water.tesselations < MAX_TESSELATIONS)
    {
        water.tesselations *= 2;
        water_generate(water);
    }
}

/**
 *  
 */
static inline void water_decreaseTesselations(water_t& water)
{
    if(water.tesselations > MIN_TESSELATIONS)
    {
        water.tesselations /= 2;
        water_generate(water);
    }
}


#endif
