#include "Context.h"

Context::Context(unsigned int w, unsigned int h) : width(w), height(h) {
	glewExperimental = GL_TRUE;
	glViewport(0, 0, this->width, this->height);
	const GLenum err = glewInit();
	if (err != GLEW_OK) {
#if LOG_ERROR
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::cout << glewGetErrorString(err) << std::endl;
#endif
		throw 1;
	}
	glEnable(GL_DEPTH_TEST);
};


void Context::initialize_context() {
};

void Context::render() const {
	glClearColor(0.01f, 0.01f, 0.02f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto obj : this->scene_graph) {
		obj->draw();
	}
}

void Context::attachObject(const RenderObject* obj) {
	this->scene_graph.push_back(obj);
}

