#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Program/DrawProgram.h"

const float REFRESH_RATE = 60.0f / 1000.0f;

class Window {
private:
	unsigned int width, height;
	GLFWwindow* window;
	float last_refresh;
	DrawProgram *draw_program;
	void process_input();
public:
	Window(unsigned int w, unsigned int h) : width(w), height(h) {};
	void attach_program(DrawProgram* p);
	void run_program();
};

#endif