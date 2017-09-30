#ifndef CONTEXT_H
#define CONTEXT_H

#include "ShaderProgram.h"
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
public:
	unsigned int width, height;

	Context(unsigned int w, unsigned int h);

	~Context() { delete this->shader_program; };

	void initialize_context();

	unsigned int createVAO() const;

	void bindVertices(unsigned int VAO, const std::vector<float> &vertices) const;

	void bindIndexes(unsigned int VAO, const std::vector<unsigned int> &indexes);

	void drawVAO(unsigned int VAO, unsigned int verticesCount) const;

	void attachShader(const char* source, SHADER_TYPE type) const;

	void setModelMatrix4(glm::mat4 m);

	void setViewMatrix4(glm::mat4 m);

	void setProjectionMatrix4(glm::mat4 m);

};

#endif
