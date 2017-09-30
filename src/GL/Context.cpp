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

unsigned int Context::createVAO() const {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}


void Context::bindIndexes(unsigned int VAO, const std::vector<unsigned int> &indexes) {
#if LOG_INFO
	for (auto it = indexes.begin(); it != indexes.end(); ++it)
		std::cout << "i: " << (*it) << std::endl;
#endif

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &indexes.front(), GL_STATIC_DRAW);

	this->index_based = true;

	glBindVertexArray(0);
};

void Context::bindVertices(unsigned int VAO, const std::vector<float> &vertices) const {
#if LOG_INFO
	for (auto it = vertices.begin(); it != vertices.end(); ++it)
		std::cout << "v: " << (*it) << std::endl;
#endif

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
#if LOG_TRACE
	std::cout << "GENERATING BUFFER " << VBO << std::endl << "BOUND VAO: " << VAO << std::endl;
#endif

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

#if LOG_TRACE
	std::cout << "BINDING COMPLETE" << std::endl;
#endif

}

void Context::drawVAO(unsigned int VAO, unsigned int verticesCount) const {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->shader_program->use_program();

	this->shader_program->setUniformMat4("view", view);
	this->shader_program->setUniformMat4("projection", projection);
	this->shader_program->setUniformMat4("model", model);

	glBindVertexArray(VAO);

	std::cout << verticesCount << std::endl;
	glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);

}

