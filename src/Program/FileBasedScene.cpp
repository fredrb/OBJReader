#include "FileBasedScene.h"
#include "../File/SceneReader.h"
#include "../File/FileReader.h"

void FileBasedScene::init_draw_program(Context *c) {
    SceneReader reader("../assets/scene/scene01.sf");

    std::vector<scene_object_t> objects = std::vector<scene_object_t>();
    reader.get_scene_object(objects);

    this->context = c;

    for (auto object : objects) {
        auto sceneObject = new SceneObject("../assets/model/" + object.model_path);
        this->initialize_object(sceneObject, glm::vec3(object.x, object.y, object.z));
        if (object.target != NULL)
            sceneObject->setTarget(object.target->x, object.target->y, object.target->z);
        this->append_to_scene(sceneObject);
    }

    this->context->initialize_context();

}

void FileBasedScene::initialize_object(SceneObject *obj, glm::vec3 position) {
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

    //glm::mat4 model_matrix;
    //obj->modelMatrix = glm::translate(model_matrix, position);
    obj->setInitialPosition(position);
    obj->createModelMatrix();
    obj->refresh(view, projection);

    obj->setUniformVec3("objectColor", glm::vec3(0.9f, 0.0f, 0.0f));
    obj->setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    obj->setUniformVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    obj->setUniformVec3("viewPos", camera.cameraPos);
}
