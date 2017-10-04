#include "OBJReaderCube.h"
#include "../File/FileReader.h"
#include "../File/OBJReader.h"

void OBJReaderCube::init_draw_program(Context* c) {
  this->obj = new SceneObject("../assets/model/cube_vn.obj");

	this->context = c;

	std::string vertexSource;
	FileReader vertexReader("../assets/shaders/vertexShader.glsl");
	vertexReader.read(vertexSource);

	this->obj->attach_shader(vertexSource, SHADER_TYPE::Vertex);

	std::string fragmentSource;
	FileReader fragmentReader("../assets/shaders/fragmentShader.glsl");
	fragmentReader.read(fragmentSource);

	this->obj->attach_shader(fragmentSource, SHADER_TYPE::Fragment);

	this->obj->prepare_data();
	this->context->attachObject(obj);

	model			  = glm::translate(model, glm::vec3(0.5f, 0.5f, -3.0f));
	model				= glm::scale(model, glm::vec3(0.5f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(this->camera.fov), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->obj->setViewMatrix4(view);
	this->obj->setModelMatrix4(model);
	this->obj->setProjectionMatrix4(projection);

	this->context->initialize_context();
};

void OBJReaderCube::on_frame(const float timestamp) {
#if LOG_TRACE
	std::cout << "DRAWING " << this->indexes.size() << " INDEXES" << std::endl;
#endif

	glm::mat4 _view;
	camera.apply_view(timestamp, _view);
	view = _view;

	this->obj->setViewMatrix4(view);
	this->obj->setModelMatrix4(model);
	this->obj->setProjectionMatrix4(projection);

	this->context->render();
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
		case KEY::QUIT:
			this->context->quit = true;
		default:
		break;
	}
};
