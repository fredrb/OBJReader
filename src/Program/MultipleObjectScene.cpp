#include "MultipleObjectScene.h"
#include "../File/FileReader.h"

void MultipleObjectScene::init_draw_program(Context* context) {
	this->obj = new SceneObject("../assets/model/bunny_vn.obj");
  // this->obj = new SceneObject("../assets/model/cube_vn.obj");

	this->context = context;

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
	view				= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(this->camera.fov), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

	this->obj->setViewMatrix4(view);
	this->obj->setModelMatrix4(obj_model);
	this->obj->setProjectionMatrix4(projection);

	this->obj->setUniformVec3("objectColor", glm::vec3(0.9f, 0.0f, 0.0f));
	this->obj->setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	this->obj->setUniformVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
	this->obj->setUniformVec3("viewPos", camera.cameraPos);

	this->context->initialize_context();
}

