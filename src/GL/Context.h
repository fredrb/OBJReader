#ifndef CONTEXT_H
#define CONTEXT_H

#include "ShaderProgram.h"
#include "RenderObject.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Context {
private:
	ShaderProgram* shader_program;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	bool index_based = false;

	std::vector<const RenderObject*> scene_graph;

public:
	unsigned int width, height;

	bool quit = false;

	Context(unsigned int w, unsigned int h);

	~Context() { delete this->shader_program; };

	void initialize_context();

	void render() const;

	void attachShader(const char* source, SHADER_TYPE type) const;

	void setModelMatrix4(glm::mat4 m);

	void setViewMatrix4(glm::mat4 m);

	void setProjectionMatrix4(glm::mat4 m);

	void attachObject(const RenderObject* obj);
};

#endif
