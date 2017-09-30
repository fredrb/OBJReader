#include <iostream>

#include "GL/Window.h"
#include "Program/DrawProgram.h"
#include "Program/StaticTriangleIndexes.h"
#include "Program/StaticCube.h"

int main() {

	Window window(800, 600);

	// DrawProgram *p = new StaticCube();
	DrawProgram *p = new StaticTriangleIndexes();

	window.attach_program(p);
	window.run_program();

	return 0;
}
