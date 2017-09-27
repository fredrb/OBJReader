#ifndef STATIC_CUBE_H
#define STATIC_CUBE_H

#include "DrawProgram.h"

class StaticCube : public DrawProgram {
private:
	unsigned int VAO;
	std::vector<float> vertices;
	Context* context;
	glm::mat4 view, model, projection;
public:
	StaticCube() {};

	void init_draw_program (Context* c) override;

	void on_frame (const float timestamp) override;

};

#endif
