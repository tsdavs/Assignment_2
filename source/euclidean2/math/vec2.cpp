/**
 *  Implementation of vec2.h
 */
#include "euclidean2/math/vec2.hpp"
#include "euclidean2/math/e_math.hpp"

#include "gl_helper.hpp"
#include "platform.hpp"

#include <cmath>
#include <cstdio>

vec2_t vec2_t::operator+(const vec2_t& rhs)
{
    vec2_t ret;

    ret.i = this->i + rhs.i;
    ret.j = this->j + rhs.j;

    return ret;
}

vec2_t& vec2_t::operator+=(const vec2_t& rhs)
{
    this->i += rhs.i;
    this->j += rhs.j;

    return *this;   
}

vec2_t vec2_t::operator*(const float rhs)
{
    vec2_t ret;

    ret.i = this->i * rhs;
    ret.j = this->j * rhs;

    return ret;
}

vec2_t& vec2_t::operator*=(const float rhs)
{
    this->i *= rhs;
    this->j *= rhs;

    return *this;   
}

float v_Magnitude(vec2_t& vec)
{
    return sqrtf((vec.i * vec.i) + (vec.j * vec.j));
}

// http://www.analyzemath.com/stepbystep_mathworksheets/vectors/vector3D_angle.html
float v_Dot(vec2_t& vec1, vec2_t& vec2)
{
    float dot;

    dot = (vec1.i * vec2.i) + (vec1.j * vec2.j);

    return dot;
}

void v_Normalize(vec2_t& vec)
{
    float mag = q_rsqrt(v_Dot(vec, vec));

    vec.i *= mag;
    vec.j *= mag;
}

float v_GetMagnitude(vec2_t& vec)
{
    return sqrtf((vec.i * vec.i) + (vec.j * vec.j));
}

float v_GetAngle(vec2_t& vec)
{
    return atanf(vec.j / vec.i);
}

void v_Draw(vec2_t& vec, float r, float g, float b, float s, bool normalize)
{
    GLCall(glColor3f(r, g, b))

    if(normalize)
    {
        float mag = v_GetMagnitude(vec);
        glBegin(GL_LINES);
            glVertex2f(vec.x-(vec.i/mag)*s, vec.y-(vec.j/mag)*s);
            glVertex2f(vec.x+(vec.i/mag)*s, vec.y+(vec.j/mag)*s);
        glEnd();
    }
    else
    {

        glBegin(GL_LINES);
            glVertex3f(vec.x, vec.y, 1.0f);
            glVertex3f(vec.x + vec.i, vec.y + vec.j, 1.0f);
        glEnd(); 
    }
}
