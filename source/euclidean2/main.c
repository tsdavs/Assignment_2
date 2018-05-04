/**
 *	Euclidean2 engine entry point
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "euclidean2/system/engine.h"
#include "platform.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialise GLUT
	e_init(argv); // Initialise euclidean2

	return EXIT_SUCCESS;
}
