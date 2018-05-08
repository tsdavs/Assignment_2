/**
 *  Implementation of window.h
 */
#include "euclidean2/system/window.hpp"

#include "platform.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

window_t* hwnd = NULL;

window_t* r_createWindow(int width, int height, const char* title)
{
    hwnd = static_cast<window_t*>(malloc(sizeof(window_t)));

    if(!hwnd)
    {
        printf("%s: hwnd == NULL!\n", __PRETTY_FUNCTION__);
        return NULL;
    }

    hwnd->title = static_cast<char*>(malloc(strlen(title)));
    
    hwnd->height = height;
    hwnd->width = width;
    strcpy(hwnd->title, title);

    printf("...created window (%dx%d)\n", width, height);

    // Now get GLUT to initialse the physical window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);

    char* glVer = const_cast<char*>(reinterpret_cast<const char*>(glGetString(GL_VERSION))); // What the fuck?!
    printf("...OpenGL context version %s\n", glVer);

    return hwnd;
}

bool r_freeWindow()
{
    if(hwnd != NULL)
    {
        free(hwnd);
        printf("...window destroyed\n");
        hwnd = NULL;
        return false;    
    }

    // We can't free a NULL pointer!
    printf("%s: Cannot Free Window (hwnd == NULL)!\n", __PRETTY_FUNCTION__);
    return false;
}

bool r_setDrawFunction(void (*drawCB)(void))
{
    if(hwnd == NULL)
    {
        printf("%s: hwnd == NULL!\n", __PRETTY_FUNCTION__);
        return false;       
    }

    if(drawCB == NULL)
    {
        printf("%s: Cannot set hwnd->r_draw() to NULL!\n", __PRETTY_FUNCTION__);
        return false;
    }

    hwnd->r_draw = drawCB;
    glutDisplayFunc(hwnd->r_draw);

    printf("...setting draw function to %p\n", drawCB);
    return true;
}

void r_setDimensions(int width, int height)
{
    if(hwnd != NULL)
    {
        hwnd->width = width;
        hwnd->height = height;
    }
}

