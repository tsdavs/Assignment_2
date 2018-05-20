/**
 *  Implementation of water.hpp
 */
#include "euclidean2/object/water.hpp"
#include "euclidean2/math/e_math.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/math/vec3.hpp"

#include "platform.hpp"

#include <cstdlib>

static constexpr float LEFT = -2.0f;
static constexpr float RIGHT = 2.0f;
static constexpr float RANGE = RIGHT - LEFT;

static ground_t ground;

void water_generate(water_t& water)
{
    float xStep = RANGE/static_cast<float>(water.tesselations);
    float zStep = xStep;
    float x = 0.0f;
    float z = 0.0f;

    for(int i = 0; i < water.tesselations; i++)
    {
        z = LEFT + static_cast<float>(i) * zStep;
        for(int j = 0; j < water.tesselations; j++)
        {
            vertex3f_t vert;

            x = LEFT + static_cast<float>(j) * xStep;
            vert.position.x = x;
            vert.position.y = 0.0f;
            vert.position.z = z;
            water.verts[i][j] = vert;
        }
    }

    
    xStep = RANGE/128;
    zStep = xStep;
    for(int i = 0; i < 128; i++)
    {
        z = LEFT + static_cast<float>(i) * zStep;
        for(int j = 0; j < 128; j++)
        {
            vertex3f_t vert;

            x = LEFT + static_cast<float>(j) * xStep;  
            vert.position.x = x;
            vert.position.y = -0.4f;
            vert.position.z = z;
            ground.verts[i][j] = vert;
        } 
    }

    material_create(water.mat, 0.0f, 0.97f, 0.97f, 1.0f, 1.0f, 1.0f, 128.0f);
    material_setAlpha(water.mat, 0.50f);

    material_create(ground.mat, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 1.0f);
    material_setAlpha(ground.mat, 1.0f);
}

void water_draw(water_t& water, bool drawNorms)
{
	glEnable(GL_BLEND);
	
	water_drawGround(ground);
	
	for(int i = 0; i < water.tesselations - 1; i++)
    {
        material_bind(water.mat);
        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j < water.tesselations; j++)
        {
            vertex3f_t v1;
            vertex3f_t v2;

            v1 = water.verts[i][j];
            v2 = water.verts[i+1][j];
            
            glNormal3f(v1.normal.i, v1.normal.j, v1.normal.k);
            glVertex3f(v1.position.x, v1.position.y, v1.position.z);
            glNormal3f(v2.normal.i, v2.normal.j, v2.normal.k);
            glVertex3f(v2.position.x, v2.position.y, v2.position.z);
        }
        glEnd();
    }

    if(drawNorms)
    {
        for(int i = 0; i < water.tesselations; i++)
        {
            for(int j = 0; j < water.tesselations; j++)
            {
			    v_Draw(water.verts[i][j].position, water.verts[i][j].normal);
            }
        }
    }
}

void water_drawGround(ground_t& ground)
{
    for(int i = 0; i < 128 - 1; i++)
    {
        material_bind(ground.mat);
        glBegin(GL_TRIANGLE_STRIP);
        for(int j = 0; j < 128; j++)
        {
            vertex3f_t v1;
            vertex3f_t v2;

            v1 = ground.verts[i][j];
            v2 = ground.verts[i+1][j];
            
            glNormal3f(v1.normal.i, v1.normal.j, v1.normal.k);
            glVertex3f(v1.position.x, v1.position.y, v1.position.z);
            glNormal3f(v2.normal.i, v2.normal.j, v2.normal.k);
            glVertex3f(v2.position.x, v2.position.y, v2.position.z);
        }
        glEnd();
    }
}

/**
 * Calculate the sine wave for a given amplitude, kx, kz
 */ 
static inline float m_calculateSine(float a, float kx, float kz, float w, float x, float z, float t)
{
    return  a * sinf(kx*x + kz*z + w*t);
}

static float m_calcDYDX(float a, float kx, float kz, float x, float z, float w, float t)
{
    return kx * a * cosf(kx*x + kz*z + w*t);
}

static float m_calcDYDZ(float a, float kx, float kz, float x, float z, float w, float t)
{
    return kz * a * cosf(kx*x + kz*z + w*t);
}

// TODO: Make these global so we can use 'extern'

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion" // Stop the compiling from complaining about loss of precision, we don't care.
void water_animate(water_t& water, float t, int numWaves)
{
	// Wave constants
	// Wave 1
    // Static cast to shut g++ up about -Wfloat-conversion!
    float a[]   = {0.13f, 0.05f, 0.15};
    float kx[]  = {2*M_PI, M_PI, -M_PI_4};
    float kz[]  = {M_PI, -2*M_PI, M_PI / 8};
    float w[]   = {M_PI, -M_PI_4, M_PI_2};


	//float dydx1, dydz1, dydx2, dydz2;
	
	for(int i = 0; i < water.tesselations; i++)
	{
        float wave = 0.0f;
        float dydx = 0.0f;
        float dydz = 0.0f;
		for(int j = 0; j < water.tesselations; j++)
		{
            float x = water.verts[i][j].position.x;
            float z = water.verts[i][j].position.z;

            for(int n = 0; n < numWaves; n++)
            {
                wave += m_calculateSine(a[n], kx[n], kz[n], w[n], x, z, t);
                dydx += m_calcDYDX(a[n], kx[n], kz[n], x, z, w[n], t);
                dydz += m_calcDYDZ(a[n], kx[n], kz[n], x, z, w[n], t);
            }

            water.verts[i][j].position.y = wave;
			
            water.verts[i][j].normal.i = -dydx;
            water.verts[i][j].normal.j = 1.0f;
            water.verts[i][j].normal.k = -dydz;
            v_Normalize(water.verts[i][j].normal);  

            wave = 0.0f;
            dydx = 0.0f;
            dydz = 0.0f;

    	}                
	}
}
#pragma GCC diagnostic pop
