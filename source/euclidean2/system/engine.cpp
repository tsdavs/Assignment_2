/**
 *	Implementation of engine.h
 */
#include "euclidean2/system/engine.hpp"
#include "euclidean2/system/window.hpp"
#include "euclidean2/camera/camera.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/system/text.hpp"

#include "platform.hpp"
#include "gl_helper.hpp"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>

#include <string>

engine_t engine;	/**< Local engine structure. Not static so we can abuse 'extern'. */
camera_t cam;

extern window_t* hwnd; // YEAH LIVE LIFE ON THE EDGE!

static void i_keyPressed(unsigned char c, int x, int y)
{
    static_cast<void>(x);
    static_cast<void>(y);

    switch(c)
    {
        case 127:
            engine.debug = !engine.debug;
            break;

        default:
            break;
    }
}

// Draw 3D axes
static void r_drawAxes(void)
{
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f); 
    glEnd();

    // Draw the y-axis in green
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Draw the z-axis in blue
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

static void e_pumpGLError(void)
{
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR)
    {
        std::string err_str = "[GL ERROR]: ";

        switch(error)
        {
        case GL_INVALID_ENUM:
            err_str += "INVALID_ENUM\n";
            break;
        case GL_INVALID_VALUE:
            err_str += "INVALID_VALUE\n";
            break;
        case GL_INVALID_OPERATION:
            err_str += "INVALID_OPERATION\n";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            err_str += "GL_INVALID_FRAMEBUFFER_OPERATION\n";
            break;
        case GL_OUT_OF_MEMORY:
            err_str += "GL_OUT_OF_MEMORY\n";
            break;
        case GL_STACK_OVERFLOW:
            err_str += "GL_STACK_OVERFLOW\n";
            break;
        case GL_STACK_UNDERFLOW:
            err_str += "GL_STACK_UNDERFLOW\n";
            break;
        default:
            err_str += "UNKNOWN!!!\n";
            break;
        }

        printf("%s\n", err_str.c_str());
    }
}

/**
 *	Engine draw function
 */
static void draw(void)
{
    char str[256];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // View stuff
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    if(engine.debug)
    {
        r_drawString(0, 0, "[ DEBUG ]");
    }

    r_drawAxes();

    e_pumpGLError();
	glutSwapBuffers();
}

void e_shutdown()
{
    printf("---- e_shutdown ----\n");
    r_freeWindow();
}

void e_update(void)
{    
    static float prev_t = -1.0f;
    float t = 0.0f;
    float dt = 0.0f;

    t = glutGet(GLUT_ELAPSED_TIME) / MILLISECOND_TIME; // Number of ms since glutInit() was called

    // Skip the first frame to prevent / 0
    // Also keep the clock running even if the sim is paused to dt doesn't become huge
    if(prev_t < 0.0f || !engine.running)
    {
        prev_t = t;
        return;
    } 

    dt = t - prev_t;

    // TODO: Game logic here!






    prev_t = t;
    
    dt = t - engine.last_frametime;

    if(dt > 0.2)
    {        
        engine.framerate = (engine.frames/dt);
        engine.dt = dt;
        engine.last_frametime = t;
        engine.frames = 0;
    }
    glutPostRedisplay();
}

void e_init(int argc, char** argv)
{
    // Walk the arguments list
    for(int i = 1; i < argc; i++) // Don't include execution string
    {
        std::string arg = std::string(argv[i]);
        printf("arg: %s\n", arg.c_str());
    }

    printf("---- e_init ----\n");
    r_createWindow(640, 480, "Test");
    r_setDrawFunction(&draw);
    
	// Engine stuff
    engine.debug            = false;
    engine.wireframe        = false;
    engine.frames           = 0;
    engine.frame_interval   = 0.2f;
    engine.last_frametime   = 0.0f;
    engine.time_elapsed     = 0.0f;
	engine.framerate 		= 0.0f;
    engine.running          = true;

    cam_init(cam, hwnd->width, hwnd->height);

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f))

	glutIdleFunc(e_update);
    glutKeyboardFunc(i_keyPressed);

    #ifdef FREEGLUT
        glutCloseFunc(e_shutdown);
    #endif

    cam.z = 5.0f;

    glutMainLoop();

    printf("Goodbye!\n");

}
