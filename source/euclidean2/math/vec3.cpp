/**
 *  Implementation of vec3.h
 */
#include "euclidean2/math/vec3.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/math/e_math.hpp"

#include "platform.hpp"

#include <cmath>
#include <cstdint>

vec3_t vec3_t::operator+(const vec3_t& rhs)
{
    vec3_t ret;

    ret.i = this->i + rhs.i;
    ret.j = this->j + rhs.j;
    ret.k = this->j + rhs.k;

    return ret;
}

vec3_t& vec3_t::operator+=(const vec3_t& rhs)
{
    this->i += rhs.i;
    this->j += rhs.j;
    this->k += rhs.k;

    return *this;   
}

vec3_t vec3_t::operator*(const float rhs)
{
    vec3_t ret;

    ret.i = this->i * rhs;
    ret.j = this->j * rhs;
    ret.k = this->j * rhs;

    return ret;
}

vec3_t& vec3_t::operator*=(const float rhs)
{
    this->i *= rhs;
    this->j *= rhs;
    this->k *= rhs;

    return *this;   
}

float v_Magnitude(vec3_t& vec)
{
    return sqrtf((vec.i * vec.i) + (vec.j * vec.j) + (vec.k + vec.k));
}

// http://www.analyzemath.com/stepbystep_mathworksheets/vectors/vector3D_angle.html
float v_Dot(vec3_t& vec1, vec3_t& vec2)
{
    float dot;

    dot = (vec1.i * vec2.i) + (vec1.j * vec2.j) + (vec1.k * vec2.k);

    return dot;
}

vec3_t v_Cross(vec3_t& vec1, vec3_t& vec2)
{
    vec3_t  ret;

    // Perform actual cross product
    ret.i = ((vec1.j * vec2.k) - (vec1.k * vec2.j));
    ret.j = -((vec1.i * vec2.k) - (vec1.k * vec2.i));
    ret.k = ((vec1.i * vec2.j) - (vec1.j * vec2.i));

    return ret;
}

void v_Normalize(vec3_t& vec)
{
    float length;

    // TODO: Some kinda 'ifdef' here

    /**
     *  This looks nefariously evil, but it makes sense when you work it out on paper.
     *
     *  Vector normal is calculated by v/||v||, which is the same as v/sqrt(||v||^2).
     *  When we factor in 1/sqrt(x), we can see that it will become v*(1/sqrt(||v||^2)), where ||v||^2 is the 
     *  dot product of the vector with itself.
     */
    length = q_rsqrt(v_Dot(vec, vec)); // This is equivalent to 1/sqrt(||v||^2)

    /**
     *  We could conversely do vec->ijk /= mag here. 
     */
    vec.i *= length;
    vec.j *= length;
    vec.k *= length;
}

float v_Angle(vec3_t& vec1, vec3_t& vec2)
{
    float dot;
    float mag1;
    float mag2;
    float ang;

    dot     = v_Dot(vec1, vec2);
    mag1    = v_Magnitude(vec1);
    mag2    = v_Magnitude(vec2);

    ang     = (dot) / (mag1 * mag2);

    return ang;
}

void v_Draw(vec3_t& pos, vec3_t& vec)
{
    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(pos.x, pos.y, pos.z);
        glVertex3f(pos.x + vec.i * 0.05, pos.y + vec.j * 0.05, pos.z + vec.k * 0.05);
    glEnd();

    glPopAttrib();
}

void v_Draw(vec3_t& pos, vec3_t& vec, float r, float g, float b)
{
    glDisable(GL_LIGHTING);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
        glVertex3f(pos.x, pos.y, pos.z);
        glVertex3f(pos.x + vec.i * 0.05, pos.y + vec.j * 0.05, pos.z + vec.k * 0.05);
    glEnd();
    glEnable(GL_LIGHTING);
}
