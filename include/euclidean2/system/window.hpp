/**
 *  Window related functions and structures
 */
#ifndef _WINDOW_H_INCLUDED
#define _WINDOW_H_INCLUDED

#include <stdbool.h>

/**
 *  Window structure. Contains information about the current window
 */
typedef struct
{
    int     width;                                      /**< Window width (in pixels) */
    int     height;                                     /**< Window height (in pixels) */
    char*   title;                                      /**< Window title */

    void (*r_draw)(void);                               /**< This window's current draw function */
    void (*w_resize)(int width, int height);            /**< This window's resize function */  
} window_t;

/**
 *  Creates a new window.
 *
 *  @param width Width we want the window to be (in pixels)
 *  @param height Height we want the window to be (in pixels)
 *  @param title Title we want this GLUT window to be
 *
 *  @return Pointer to a new window struct
 */
window_t* r_createWindow(int width, int height, const char* title);

/**
 *  Frees this window
 */
bool r_freeWindow();

/**
 *  Sets the callback function for this window
 *
 *  @param drawCB Pointer to draw callback function
 */
bool r_setDrawFunction(void (*drawCB)(void));

/**
 *  Update the dimensions of our window
 */
void r_setDimensions(int width, int height);

#endif

