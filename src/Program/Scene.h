#ifndef SCENE_H
#define SCENE_H

#include "DrawProgram.h"
#include "../GL/Object/SceneObject.h"
#include "../Camera.h"

class Scene : public DrawProgram {
private:
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;

	glm::vec3 obj_position = glm::vec3(0.5f, 0.5f, -3.0f);

	void toggle_scale();

	void rotate();

	bool big_scale = false;


protected:
	Camera camera;

	SceneObject *obj;
	SceneObject *light;
	Context* context;

	glm::mat4 view, obj_model, light_model, projection;

	std::vector<SceneObject*> objects;

	void append_to_scene(SceneObject* object);

public:
	// virtual void init_draw_program (Context* c) override = 0;

	void on_frame (const float timestamp) override;

	void on_key_pressed(const KEY key) override;

	void on_mouse_moved(double, double) override;

	void on_window_resize(int, int) override;


};

#endif
