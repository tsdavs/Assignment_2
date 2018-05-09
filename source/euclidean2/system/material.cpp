/**
 *  Implementation of material.hpp
 */
#include "euclidean2/system/material.hpp"

//void material_create(material_t& mat, GLfloat amb_r, GLfloat amb_g, GLfloat amb_b, GLfloat amb_a, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat dif_a, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat spec_a, GLfloat shininess)
void material_create(material_t& mat, GLfloat amb_r, GLfloat amb_g, GLfloat amb_b, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat shininess)
{
    mat.ambient.x   = amb_r;
    mat.ambient.y   = amb_g;
    mat.ambient.z   = amb_b;
    mat.ambient.w   = 1.0f;

    mat.diffuse.x   = dif_r;
    mat.diffuse.y   = dif_g;
    mat.diffuse.z   = dif_b;
    mat.diffuse.w   = 1.0f;

    mat.specular.x  = spec_r;
    mat.specular.y  = spec_g;
    mat.specular.z  = spec_b;
    mat.specular.w  = 1.0f;

    mat.shininess   = shininess;
}

void material_bind(material_t& mat)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,  reinterpret_cast<float*>(&mat.ambient));
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  reinterpret_cast<float*>(&mat.diffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, reinterpret_cast<float*>(&mat.specular));
}