#ifndef OBJ_READER_CUBE_PROGRAM_H
#define OBJ_READER_CUBE_PROGRAM_H

#include "DrawProgram.h"
#include "../Camera.h"
#include "../GL/Object/SceneObject.h"

class OBJReaderCube : public DrawProgram {
private:
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
	Context* context;
	glm::mat4 view, obj_model, light_model, projection;
	Camera camera;

	glm::vec3 obj_position = glm::vec3(0.5f, 0.5f, -3.0f);

	SceneObject *obj;
	SceneObject *light;

	void toggle_scale();

	void rotate();

	bool big_scale = false;

public:
	void init_draw_program (Context* c) override;

	void on_frame (const float timestamp) override;

	void on_key_pressed(const KEY key) override;

	void on_mouse_moved(double, double) override;

	void on_window_resize(int, int) override;

};

#endif
