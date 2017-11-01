#include <iostream>

#include "GL/Window.h"
#include "Program/DrawProgram.h"
#include "Program/StaticTriangleIndexes.h"
#include "Program/StaticCube.h"
#include "Program/OBJReaderCube.h"
#include "Program/MultipleObjectScene.h"

int main() {

	Window window(800, 600);

	// DrawProgram *p = new StaticCube();
	// DrawProgram *p = new StaticTriangleIndexes();
	// DrawProgram *p = new OBJReaderCube();
	DrawProgram *p = new MultipleObjectScene();

	window.attach_program(p);
	window.run_program();

	return 0;
}
