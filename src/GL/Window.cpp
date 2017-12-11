#include "Window.h"
#include "Context.h"

#include <iostream>

DrawProgram* GLOBAL_PROGRAM;

void Window::attach_program(DrawProgram* p) {
	GLOBAL_PROGRAM = p;
}

void Window::process_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	GLOBAL_PROGRAM->on_mouse_moved(xpos, ypos);
}

void Window::on_window_resize(GLFWwindow* w, int width, int height) {
	std::cout << "Window resize" << std::endl;
	GLOBAL_PROGRAM->on_window_resize(width, height);
}

void Window::process_input() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::UP);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::LEFT);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::DOWN);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::RIGHT);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::QUIT);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::SCALE);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		GLOBAL_PROGRAM->on_key_pressed(KEY::ROTATE);
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (GLOBAL_PROGRAM == NULL) {
		std::cout << "Failed to initialize window without a valid program" << std::endl;
		throw 1;
	};

	Context context(this->width, this->height);
	GLOBAL_PROGRAM->init_draw_program(&context);
	glfwSetCursorPosCallback(this->window, this->process_mouse_callback);
	glfwSetFramebufferSizeCallback(this->window, this->on_window_resize);

	while (!glfwWindowShouldClose(window) && !context.quit) {
		float t = glfwGetTime() * 1000;
		if (t - this->last_refresh > REFRESH_RATE) {
#if LOG_TRACE
			std::cout << "CURRENT TIME: "<< t << " - Last refresh at: " << this->last_refresh << " - Refresh rate: " << REFRESH_RATE << std::endl;
#endif
			this->process_input();
			GLOBAL_PROGRAM->on_frame(glfwGetTime());
			glfwSwapBuffers(window);
			glfwPollEvents();
			this->last_refresh = glfwGetTime() * 1000;
		}
	}

	glfwTerminate();
}
