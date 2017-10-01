#ifndef OBJ_READER_CUBE_PROGRAM_H
#define OBJ_READER_CUBE_PROGRAM_H

#include "DrawProgram.h"

class OBJReaderCube : public DrawProgram {
private:
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
	Context* context;
	glm::mat4 view, model, projection;
public:
	OBJReaderCube() {};

	void init_draw_program (Context* c) override;

	void on_frame (const float timestamp) override;

};

#endif
