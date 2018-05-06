/**
 *	Implementation of engine.h
 */
#include "euclidean2/system/engine.hpp"
#include "euclidean2/system/window.hpp"

#include "platform.hpp"
#include "gl_helper.hpp"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

engine_t engine;	/**< Local engine structure. Not static so we can abuse 'extern'. */

/**
 *	Engine draw function
 */
static void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glutSwapBuffers();
}

void e_update(void)
{

}

void e_init(char** argv)
{
    r_createWindow(640, 480, "Test");
    r_setDrawFunction(&draw);
    
	// Engine stuff
    engine.debug            = false;
    engine.wireframe        = false;
    engine.frames           = 0;
    engine.frame_interval   = 0.2;
    engine.last_frametime   = 0.0f;
    engine.time_elapsed     = 0.0f;
	engine.framerate 		= 0.0f;

	GLCall(glClearColor(0.0f, 1.0f, 0.0f, 1.0f))

	glutIdleFunc(e_update);

    glutMainLoop();

}
