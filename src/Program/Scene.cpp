#include "Scene.h"
#include "../GL/Object/SceneObject.h"

void Scene::on_frame(const float timestamp) {
#if LOG_TRACE
	std::cout << "DRAWING " << this->indexes.size() << " INDEXES" << std::endl;
#endif

	glm::mat4 _view;
	camera.apply_view(timestamp, _view);
	view = _view;

	for (auto obj : objects) {
        obj->updatePosition();
		obj->refresh(view, projection);

		obj->setUniformVec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
		obj->setUniformVec3("viewPos", camera.cameraPos);

//		obj->setUniformVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//		obj->setUniformVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
//		obj->setUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		obj->setFloat("material.shininess", 90.0f);
	}

	this->context->render();
};

void Scene::on_mouse_moved(double xpos, double ypos) {
	camera.move_mouse(xpos, ypos);
}


void Scene::toggle_scale() {
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

void Scene::on_window_resize(int width, int height) {
	this->context->updateWindowSize(width, height);
}

void Scene::rotate() {
	this->obj_model = glm::rotate(this->obj_model, glm::radians(2.0f), glm::vec3(0.0f, 0.80f, 0.0f));
}

void Scene::on_key_pressed(const KEY key) {
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
}

void Scene::append_to_scene(SceneObject *object) {
    this->context->attachObject(object);
	this->objects.push_back(object);
};
