#ifndef STATIC_TRIANGLE_INDEX
#define STATIC_TRIANGLE_INDEX

#include "DrawProgram.h"

class StaticTriangleIndexes : public DrawProgram {
private:
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
	Context* context;
	glm::mat4 view, model, projection;
public:
	StaticTriangleIndexes() {};

	void init_draw_program (Context* c) override;

	void on_frame (const float timestamp) override;

	void on_key_pressed(const KEY key) override {  };

	void on_mouse_moved(double x, double y) override {  };

};

#endif
