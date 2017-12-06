#include "MultipleObjectScene.h"
#include "../File/FileReader.h"

void MultipleObjectScene::init_draw_program(Context* context) {
	auto bunny = new SceneObject("../assets/model/bunny_vn.obj");
   	auto cow = new SceneObject("../assets/model/cow/uvmappedcow.obj");

	this->context = context;

    glm::mat4 model_matrix;
    this->initialize_object(bunny, glm::translate(model_matrix, glm::vec3(0.5f, 0.5f, -3.0f)));
    this->initialize_object(cow, glm::translate(model_matrix, glm::vec3(0.8f, 0.1f, -2.5f)));

    this->append_to_scene(bunny);
    this->append_to_scene(cow);

	this->context->initialize_context();
}

void MultipleObjectScene::initialize_object(SceneObject *obj, glm::mat4 model) {
    std::string vertexSource;
    FileReader vertexReader("../assets/shaders/vertexShader.glsl");
    vertexReader.read(vertexSource);

    obj->attach_shader(vertexSource, SHADER_TYPE::Vertex);

    std::string fragmentSource;
    FileReader fragmentReader("../assets/shaders/fragmentShader.glsl");
    fragmentReader.read(fragmentSource);

    obj->attach_shader(fragmentSource, SHADER_TYPE::Fragment);

    obj->prepare_data();

    view		= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection	= glm::perspective(glm::radians(this->camera.fov), (float)this->context->width / (float)this->context->height, 0.1f, 100.0f);

    //obj->modelMatrix = model;
    obj->refresh(view, projection);

    obj->setUniformVec3("objectColor", glm::vec3(0.9f, 0.0f, 0.0f));
    obj->setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    obj->setUniformVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    obj->setUniformVec3("viewPos", camera.cameraPos);
}


