
/**
 *	Engine related structures and functions
 */
#ifndef _ENGINE_H_INCLUDED
#define _ENGINE_H_INCLUDED

#include "euclidean2/system/window.hpp"

#include <cstdint>

/**
 *	Engine 'class'. Contains function pointers to the update, input and render methods.
 */
typedef struct
{
	void		(*update)();	/**< Engine idle update loop */
	
	bool        running;            /**< Is the game currently running??? */
    bool        debug;              /**< Is debug mode enabled? */
    bool        wireframe;          /**< Should we draw in wireframe mode? */

    // Timing related stuff
    float       time_elapsed;       /**< Elapsed time since our program started (in ms) */
    float       framerate;          /**< Current frame rate */
    float       dt;
    float       last_frametime;
    float       frame_interval;             
	uint64_t 	frames; 			/**< Frame count */
} engine_t;


/**
 *  Engine initilisation routine. Gets us out of main.
 *
 *  @param argc Number of arguments passed
 *  @param argv Arguments passed from the command line
 */
void e_init(int argc, char** argv);

/**
 *  Engine shutdown function
 */
void e_shutdown(void);




#endif
