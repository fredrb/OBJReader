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

	this->vertices = std::vector<float>();
	for (auto d : data.vertices) {
		this->vertices.push_back(d.x);
		this->vertices.push_back(d.y);
		this->vertices.push_back(d.z);
	}

	this->indexes = std::vector<unsigned int>();
	for (auto d : data.faces) {
		this->indexes.push_back(d.x_position - 1);
		this->indexes.push_back(d.y_position - 1);
		this->indexes.push_back(d.z_position - 1);
	}

	model				= glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(this->camera.fov), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

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

/*
	glm::mat4 _model;
	_model = glm::rotate(_model, (float)timestamp * glm::radians(-155.0f), glm::vec3(0.0f, 0.5f, 0.0f));
	model = _model;
*/

	glm::mat4 _view;
	camera.apply_view(timestamp, _view);
	view = _view;

	this->context->setViewMatrix4(view);
	this->context->setModelMatrix4(model);
	this->context->setProjectionMatrix4(projection);


	this->context->drawVAO(this->VAO, this->indexes.size());
};

void OBJReaderCube::on_mouse_moved(double xpos, double ypos) {
	camera.move_mouse(xpos, ypos);
}

void OBJReaderCube::on_key_pressed(const KEY key) {
#if LOG_WARN
	std::cout << "Key pressed: " << key << std::endl;
#endif

	switch(key) {
		case KEY::DOWN:
			camera.move_down();
		break;
		case KEY::UP:
			camera.move_up();
		break;
		case KEY::LEFT:
			camera.move_left();
		break;
		case KEY::RIGHT:
			camera.move_right();
		break;
		default:
		break;
	}
};
