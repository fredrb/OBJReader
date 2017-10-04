#include "OBJReaderCube.h"
#include "../File/FileReader.h"
#include "../File/OBJReader.h"

void OBJReaderCube::init_draw_program(Context* c) {
  this->obj = new SceneObject("../assets/model/bunny_vn.obj");

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

	obj_model	  = glm::translate(obj_model, glm::vec3(0.5f, 0.5f, -3.0f));
	// obj_model	  = glm::scale(obj_model, glm::vec3(3.0f));
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(this->camera.fov), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->obj->setViewMatrix4(view);
	this->obj->setModelMatrix4(obj_model);
	this->obj->setProjectionMatrix4(projection);

	this->obj->setUniformVec3("objectColor", glm::vec3(0.9f, 0.0f, 0.0f));
	this->obj->setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	this->obj->setUniformVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));

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
	this->obj->setProjectionMatrix4(projection);
	this->obj->setModelMatrix4(obj_model);

	this->context->render();
};

void OBJReaderCube::on_mouse_moved(double xpos, double ypos) {
	camera.move_mouse(xpos, ypos);
}


void OBJReaderCube::toggle_scale() {
	glm::mat4 model;
	model = glm::translate(model, this->obj_position);

	if (!this->big_scale) {
		model = glm::scale(model, glm::vec3(3.0f));
		this->big_scale = true;
	} else {
		model = glm::scale(model, glm::vec3(1.0f));
		this->big_scale = false;
	}

	this->obj_model = model;
}

void OBJReaderCube::on_window_resize(int width, int height) {
	this->context->updateWindowSize(width, height);
}

void OBJReaderCube::rotate() {
	this->obj_model = glm::rotate(this->obj_model, glm::radians(50.0f), glm::vec3(0.0f, 0.3f, 0.0f));
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
		break;
		case KEY::SCALE:
			this->toggle_scale();
		break;
		case KEY::ROTATE:
			this->rotate();
		break;
		default:
		break;
	}
};
