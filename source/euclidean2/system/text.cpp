/**
 *  Implementation of text.hpp
 */
#include "euclidean2/system/text.hpp"

#include "platform.hpp"

void r_drawChar(int x, int y, int c)
{
    int width;
    int height;

    // First we need to save some OpenGL states on the attribute stack
    glPushAttrib(GL_VIEWPORT_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT); // Save the current viewport info, enabled info and context information

    // Save the current projection matrix (so we can restore it later)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

    // Now we need to set up our MODELVIEW matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, height - 13 - y);

    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);

    glPopMatrix(); // Restore MODELVIEW

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}

void r_drawString(int x, int y, const char* msg)
{
    while(*msg != '\0')
    {
        if(*msg == '\n')
        {
            y += 13;
            x = 0;
            msg++;
            continue;
        }

        r_drawChar(x, y, *msg++);
        
        x += 8;
    }
}