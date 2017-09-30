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

	model				= glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(45.0f), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);

	this->context->initialize_context();

	this->vertices = {
		 0.5f,  0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.9f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   0.4f, 1.0f, 0.0f,

		 0.5f,  0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		-0.5f, -0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		-0.5f,  0.5f, 1.0f,   0.4f, 1.0f, 0.0f,

/*
		 0.5f,  0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		-0.5f, -0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
*/

		 0.5f, 0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, 0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		-0.5f, 0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,   0.4f, 1.0f, 0.0f,

		 0.5f, -0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		-0.5f, -0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.4f, 1.0f, 0.0f,

		 0.5f, -0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		 0.5f,  0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,   0.4f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.0f,   0.4f, 1.0f, 0.0f,
		-0.5f, -0.5f, 1.0f,   0.9f, 0.0f, 0.0f,
		-0.5f,  0.5f, 1.0f,   0.4f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   0.4f, 1.0f, 0.0f,


  };

  this->indexes = {
    0, 1, 3,
    1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		8, 9, 11,
		9, 10, 11,
		12, 13, 15,
		13, 14, 15,
		16, 17, 19,
		17, 18, 19,
		20, 21, 23,
		21, 22, 23
  };

	this->VAO = this->context->createVAO();
	this->context->bindVertices(this->VAO, this->vertices);
	this->context->bindIndexes(this->VAO, this->indexes);
};

void StaticTriangleIndexes::on_frame(const float timestamp) {

	glm::mat4 _model;
	_model = glm::rotate(_model, (float)timestamp * glm::radians(-155.0f), glm::vec3(1.0f, 0.5f, -0.3f));
	model = _model;

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);

	this->context->drawVAO(this->VAO, this->indexes.size());
};
