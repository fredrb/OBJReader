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

	SceneObject *obj;
	SceneObject *light;
public:
	void init_draw_program (Context* c) override;

	void on_frame (const float timestamp) override;

	void on_key_pressed(const KEY key) override;

	void on_mouse_moved(double, double) override;

};

#endif
