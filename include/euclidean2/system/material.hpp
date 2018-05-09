/**
 *  Material structure and functions
 */
#ifndef _MATERIAL_HPP_INCLUDED_
#define _MATERIAL_HPP_INCLUDED_

#include "euclidean2/vecd.hpp"
#include "platform.hpp"

struct material_t
{
    vec4f_t     ambient;        /**< This material's ambient color */
    vec4f_t     diffuse;        /**< This material's diffuse color */
    vec4f_t     specular;       /**< This material's specular color */
    GLfloat     shininess;      /**< How shiny this material is */
};

/**
 *  Create a materials
 */
//void material_create(material_t& mat, GLfloat amb_r, GLfloat amb_g, GLfloat amb_b, GLfloat amb_a, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat dif_a, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat spec_a, GLfloat shininess);
void material_create(material_t& mat, GLfloat amb_r, GLfloat amb_g, GLfloat amb_b, GLfloat dif_r, GLfloat dif_g, GLfloat dif_b, GLfloat spec_r, GLfloat spec_g, GLfloat spec_b, GLfloat shininess);


/**
 *  Bind a material for use
 */
void material_bind(material_t& mat);



#endif