/**
 *  Cross platform OpenGL header file
 */
#ifndef _PLATFORM_H_INCLUDED_
#define _PLATFORM_H_INCLUDED

#if defined(_WIN32) && defined(_MSC_VER) // Only inlcude windows.h if we're using Windows AND a non GNU compliler!
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif


#endif // Header guard

