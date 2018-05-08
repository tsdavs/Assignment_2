/**
 *	Euclidean2 engine entry point
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "euclidean2/system/engine.hpp"
#include "platform.hpp"

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialise GLUT
    e_init(argc, argv); // Initialise euclidean2

	return EXIT_SUCCESS;
}
