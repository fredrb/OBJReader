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

	this->shader_program = new ShaderProgram();
	glEnable(GL_DEPTH_TEST);

};

void Context::attachShader(const char* source, SHADER_TYPE type) const {
	this->shader_program->load_shader_file(source, type);
};

void Context::setViewMatrix4(glm::mat4 mat) {
	this->view = mat;
}

void Context::setModelMatrix4(glm::mat4 mat) {
	this->model = mat;
}

void Context::setProjectionMatrix4(glm::mat4 mat) {
	this->projection = mat;
}

void Context::initialize_context() {
	this->shader_program->link_program();
	this->shader_program->setUniformMat4("model", model);
	this->shader_program->setUniformMat4("view", view);
	this->shader_program->setUniformMat4("projection", projection);
};

void Context::render() const {
	glClearColor(0.01f, 0.01f, 0.02f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->shader_program->use_program();

	this->shader_program->setUniformMat4("view", view);
	this->shader_program->setUniformMat4("projection", projection);
	this->shader_program->setUniformMat4("model", model);

	for (auto obj : this->scene_graph) {
		obj->draw();
	}
}

void Context::attachObject(const RenderObject* obj) {
	this->scene_graph.push_back(obj);
}

