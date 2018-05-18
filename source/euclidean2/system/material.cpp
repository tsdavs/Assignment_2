/**
 *  Implementation of material.hpp
 */
#include "euclidean2/system/material.hpp"

void material_create(material_t& mat, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat shininess)
{
    mat.diffuse.x   = dif_r;
    mat.diffuse.y   = dif_g;
    mat.diffuse.z   = dif_b;
    mat.diffuse.w   = 1.0f;

    mat.specular.x  = spec_r;
    mat.specular.y  = spec_g;
    mat.specular.z  = spec_b;
    mat.specular.w  = 0.0f;

    mat.shininess   = shininess;
}

void material_setAlpha(material_t& mat, GLfloat dif_a)
{
    mat.diffuse.w = dif_a;
}

void material_bind(material_t& mat)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,  reinterpret_cast<float*>(&mat.diffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, reinterpret_cast<float*>(&mat.specular));
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess);
}
