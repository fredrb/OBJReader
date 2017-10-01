#include "OBJReaderCube.h"
#include "../File/FileReader.h"
#include "../File/OBJReader.h"

void OBJReaderCube::init_draw_program(Context* c) {
	this->context = c;

	std::string vertexSource;
	FileReader vertexReader("../assets/shaders/vertexShader.glsl");
	vertexReader.read(vertexSource);

	this->context->attachShader(vertexSource.c_str(), SHADER_TYPE::Vertex);

	std::string fragmentSource;
	FileReader fragmentReader("../assets/shaders/fragmentShader.glsl");
	fragmentReader.read(fragmentSource);

	this->context->attachShader(fragmentSource.c_str(), SHADER_TYPE::Fragment);

	OBJReader objReader("../assets/model/cube.obj");
	t_obj_data data = objReader.get_obj_data();

	this->vertices = data.vertices;
	this->indexes = data.faces;

	model				= glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(30.0f), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);

	this->context->initialize_context();

	this->VAO = this->context->createVAO();
	this->context->bindVertices(this->VAO, this->vertices);
	this->context->bindIndexes(this->VAO, this->indexes);
};

void OBJReaderCube::on_frame(const float timestamp) {
#if LOG_TRACE
	std::cout << "DRAWING " << this->indexes.size() << " INDEXES" << std::endl;
#endif

	glm::mat4 _model;
	_model = glm::rotate(_model, (float)timestamp * glm::radians(-155.0f), glm::vec3(0.0f, 0.5f, 0.0f));
	model = _model;

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);


	this->context->drawVAO(this->VAO, this->indexes.size());
};
