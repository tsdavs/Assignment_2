/**
 *	Euclidean2 engine entry point
 */
#include <cstdio>
#include <cstdlib>
#include <cstdlib>

#include "euclidean2/system/engine.hpp"
#include "platform.hpp"

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialise GLUT
	e_init(argv); // Initialise euclidean2

	return EXIT_SUCCESS;
}
