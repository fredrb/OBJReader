#ifndef CONTEXT_H
#define CONTEXT_H

#include "Object/RenderObject.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Context {
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	bool index_based = false;

	std::vector<const RenderObject*> scene_graph;

public:
	unsigned int width, height;

	bool quit = false;

	Context(unsigned int w, unsigned int h);

	~Context() {};

	void initialize_context();

	void render() const;

	void attachObject(const RenderObject* obj);
};

#endif
