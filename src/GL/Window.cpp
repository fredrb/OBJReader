#include "Window.h"
#include "Context.h"

#include <iostream>

void Window::attach_program(DrawProgram* p) {
	this->draw_program = p;
}

void Window::process_input() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		this->draw_program->on_key_pressed(KEY::UP);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		this->draw_program->on_key_pressed(KEY::LEFT);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
		this->draw_program->on_key_pressed(KEY::DOWN);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		this->draw_program->on_key_pressed(KEY::RIGHT);
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
			this->process_input();
			this->draw_program->on_frame(glfwGetTime());
			glfwSwapBuffers(window);
			glfwPollEvents();
			this->last_refresh = glfwGetTime() * 1000;
		}
	}


}
