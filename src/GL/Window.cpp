#include "Window.h"
#include "Context.h"

#include <iostream>

void Window::attach_program(DrawProgram* p) {
	this->draw_program = p;
}

void Window::run_program() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to initialize window" << std::endl;
		glfwTerminate();
		throw 1;
	}

	glfwMakeContextCurrent(window);

	if (this->draw_program == NULL) {
		std::cout << "Failed to initialize window without a valid program" << std::endl;
		throw 1;
	};

	Context context(this->width, this->height);
	this->draw_program->init_draw_program(&context);

	while (!glfwWindowShouldClose(window)) {
		float t = glfwGetTime() * 1000;
		if (t - this->last_refresh > REFRESH_RATE) {
#if LOG_TRACE
			std::cout << "CURRENT TIME: "<< t << " - Last refresh at: " << this->last_refresh << " - Refresh rate: " << REFRESH_RATE << std::endl;
#endif
			this->draw_program->on_frame(glfwGetTime());
			glfwSwapBuffers(window);
			glfwPollEvents();
			this->last_refresh = glfwGetTime() * 1000;
		}
	}


}
