#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <functional>
#include <iostream>
#include <GL/glew.h>

#include <glm/glm.hpp>

typedef std::function<void(std::string)> t_error_callback;

enum SHADER_TYPE {
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER
};

static void default_error_function(std::string err) { std::cout << err << std::endl; }

class ShaderProgram {
private:
	unsigned int shader_id;
	t_error_callback error_callback = default_error_function;
public:
	ShaderProgram();

	void load_shader_file(const char* source, SHADER_TYPE type) const;

	void link_program() const;

	void use_program() const;

	unsigned int get_shader_id() const;

	void attach_error_callback(t_error_callback fn);

	void setUniformMat4(const char* name, const glm::mat4 &mat) const;

	void setUniformVec3(const char* name, const glm::vec3 &vec) const;
};

#endif
