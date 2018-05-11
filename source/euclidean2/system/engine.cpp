/**
 *	Implementation of engine.h
 */
#include "euclidean2/system/engine.hpp"
#include "euclidean2/system/window.hpp"
#include "euclidean2/camera/camera.hpp"
#include "euclidean2/math/angle.hpp"
#include "euclidean2/system/text.hpp"

#include "euclidean2/system/light.hpp"
#include "euclidean2/system/material.hpp"

#include "platform.hpp"
#include "gl_helper.hpp"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>

#include <string>

static constexpr float MILLISECOND_TIME = 1000.0f;

engine_t engine;	/**< Local engine structure. Not static so we can abuse 'extern'. */
camera_t cam;

extern window_t* hwnd; // YEAH LIVE LIFE ON THE EDGE!

static void i_keyPressed(unsigned char c, int x, int y)
{
    static_cast<void>(x);
    static_cast<void>(y);

    switch(c)
    {

        case 'w':
            cam_translate(cam, 0.6f * engine.dt);
            break;

        case 's':
            cam_translate(cam, -0.6f * engine.dt);
            break;

        case 'p':
            engine.running = !engine.running;
            break;

        case 127: // DEL
            engine.debug = !engine.debug;
            break;

        case 27: // ESC
            #ifdef FREEGLUT
                glutLeaveMainLoop();
            #else
                exit(0);
            #endif
            break;

        default:
            break;
    }
}

static void i_mouseMotion(int x, int y)
{
    if(!engine.running)
        return;

    float dx = static_cast<float>(x) - static_cast<float>(hwnd->width / 2);
    float dy = static_cast<float>(y) - static_cast<float>(hwnd->height / 2);

    cam_yaw(cam, dx * engine.dt);
    cam_pitch(cam, dy * engine.dt);
    cam_update(cam);
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


light_t l1;
material_t m1;


/**
 *	Engine draw function
 */
static void draw(void)
{
    char str[512];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(!engine.running)
		return;

    // View stuff
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z, cam.x + cam.lx, cam.y + cam.ly, cam.z + cam.lz, 0.0f, 1.0f, 0.0f);

	light_enable(l1);

    if(engine.debug)
    {
        r_drawString(0, 0, "[ DEBUG ]");
		r_drawString(0, 13, "[ CAM ]");
        sprintf(str, "cam.x     = %f\ncam.y     = %f\ncam.z     = %f\ncam.lx    = %f\ncam.ly    = %f\ncam.lz    = %f\ncam.pitch = %f\ncam.yaw   = %f\n", cam.x, cam.y, cam.z, cam.lx, cam.ly, cam.lz, cam.pitch, cam.yaw);
        r_drawString(0, 26, str);
		r_drawString(0, 143, "[ LIGHTING ]");
		sprintf(str, "activeLights = %d", light_getActiveLightCount());
		r_drawString(0, 156, str);
    }

    r_drawAxes();

	glEnable(GL_LIGHTING);

    light_translate(l1, 0.0f, 0.0f, -0.02f);
    material_bind(m1);
    glutSolidTeapot(0.4f);
   
	light_draw(l1);
	light_disable(l1);
	glDisable(GL_LIGHTING);

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

    t = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / MILLISECOND_TIME; // Number of ms since glutInit() was called

    // Skip the first frame to prevent / 0
    // Also keep the clock running even if the sim is paused to dt doesn't become huge
    if(prev_t < 0.0f || !engine.running)
    {
  		prev_t = t;	
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        return;
    } 

    if(engine.running)
    {
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(hwnd->width/2, hwnd->height/2);
    }

    dt = t - prev_t;



    prev_t = t;
    dt = t - engine.last_frametime;
    if(dt > 0.2)
    {        
        engine.framerate = static_cast<float>(engine.frames)/dt;
        engine.dt = dt;
        engine.last_frametime = t;
        engine.frames = 0;
    }
    glutPostRedisplay();
}

static void e_glInit()
{
    glShadeModel(GL_SMOOTH);    // Set the shading model
    glEnable(GL_DEPTH_TEST);    // Enable the Depth test for depth buffer
    glDepthFunc(GL_LESS);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Lighting 
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

    // Initialize OpenGL paramaters
    e_glInit();
    
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

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	glutIdleFunc(e_update);
    glutKeyboardFunc(i_keyPressed);
    glutPassiveMotionFunc(i_mouseMotion);

    #ifdef FREEGLUT
        glutCloseFunc(e_shutdown);
    #endif

    cam.z = 5.0f;

    light_create(l1, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 1.0f, 0.3f, 0.02f, GL_LIGHT0);
    material_create(m1, 0.135f, 0.2225f, 0.1575f, 0.54f, 0.89f, 0.63f, 0.316228f, 0.316228f, 0.316228f, 12.8f);

    glutMainLoop();
}
