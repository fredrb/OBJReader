#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "../File/OBJReader.h"
#include <GL/glew.h>

class RenderObject {

private:
	t_obj_data raw_data;
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
public:
	RenderObject(std::string from_path);

	void prepare_data();

	void draw() const;
};

#endif
