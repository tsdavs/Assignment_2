/**
 *  Material structure and functions
 */
#ifndef _MATERIAL_HPP_INCLUDED_
#define _MATERIAL_HPP_INCLUDED_

#include "euclidean2/vecd.hpp"
struct material_t
{
    vec4f_t     diffuse;        /**< This material's diffuse color */
    vec4f_t     specular;       /**< This material's specular color */
    GLfloat     shininess;      /**< How shiny this material is */
};

/**
 *  Create a material
 */
void material_create(material_t& mat, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat shininess);

/**
 *  Set the diffuse color of our material
 */
void material_setDiffuse(material_t& mat, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat dif_a);

/**
 *  Set transparency of material diffuse color
 */
void material_setAlpha(material_t& mat, GLfloat dif_a);

/**
 *  Set the shininess of this material
 */
void material_setShininess(material_t& mat, GLfloat shininess);

/**
 *  Bind a material for use
 */
void material_bind(material_t& mat);



#endif
