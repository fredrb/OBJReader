#include "StaticTriangleIndexes.h"
#include "../File/FileReader.h"

void StaticTriangleIndexes::init_draw_program(Context* c) {
	this->context = c;

	std::string vertexSource;
	FileReader vertexReader("../assets/shaders/vertexShader.glsl");
	vertexReader.read(vertexSource);

	this->context->attachShader(vertexSource.c_str(), SHADER_TYPE::Vertex);

	std::string fragmentSource;
	FileReader fragmentReader("../assets/shaders/fragmentShader.glsl");
	fragmentReader.read(fragmentSource);

	this->context->attachShader(fragmentSource.c_str(), SHADER_TYPE::Fragment);

	model				= glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(45.0f), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);

	this->context->initialize_context();
	this->vertices = {
		 0.5f,  0.5f, 0.1f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.1f,   0.4f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.1f,   0.4f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.1f,   0.4f, 1.0f, 0.0f
  };

  this->indexes = {
    0, 1, 3,
    1, 2, 3
  };

	this->VAO = this->context->createVAO();
	this->context->bindVertices(this->VAO, this->vertices);
	this->context->bindIndexes(this->VAO, this->indexes);
};

void StaticTriangleIndexes::on_frame(const float timestamp) {
#if LOG_TRACE
	std::cout << "DRAWING " << this->indexes.size() << " INDEXES" << std::endl;
#endif

/*
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.5f, 1.0f, 2.7f));
	this->context->setModelMatrix4(model);
*/

	this->context->drawVAO(this->VAO, this->indexes.size());
};
