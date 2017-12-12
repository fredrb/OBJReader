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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto it = this->scene_graph.begin(); it < this->scene_graph.end(); ++it) {
#if LOG_WARN
	std::cout << "DRAWING OBJECT FROM SCENE GRAPH : " << std::distance(this->scene_graph.begin(), it) << std::endl;
#endif
		(*it)->draw();
	}
}

void Context::attachObject(const RenderObject* obj) {
	this->scene_graph.push_back(obj);
}


void Context::updateWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
	glViewport(0, 0, this->width, this->height);
}
