#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	this->shader_id = glCreateProgram();
}

void ShaderProgram::load_shader_file(const char* source, SHADER_TYPE type) const {
	unsigned int id = glCreateShader((unsigned int)type);
	glShaderSource(id, 1, &source, NULL);

	glCompileShader(id);
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
#if LOG_ERROR
		char infoLog[512];
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "SOURCE: " << source << std::endl;
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
#endif
		throw 1;
	}

	glAttachShader(this->shader_id, id);
	glDeleteShader(id);
}

void ShaderProgram::link_program() const {
#if LOG_WARN
	std::cout << "Linking shader program" << std::endl;
#endif
	glLinkProgram(this->shader_id);
	int success;
	glGetProgramiv(this->shader_id, GL_LINK_STATUS, &success);
	if (!success) {
#if LOG_ERROR
		char infoLog[512];
		glGetProgramInfoLog(this->shader_id, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
#endif
		throw 1;
	}
}

void ShaderProgram::use_program() const {
#if LOG_WARN
	std::cout << "USING SHADER PROGRAM " << this->shader_id << std::endl;
#endif
	glUseProgram(this->shader_id);
}

unsigned int ShaderProgram::get_shader_id() const {
	return this->shader_id;
}

void ShaderProgram::attach_error_callback(t_error_callback fn) {
#if LOR_WARN
	std::cout << "Attaching error callback" << std::endl;
#endif
	this->error_callback = fn;
}

void ShaderProgram::setUniformMat4(const char* name, const glm::mat4 &mat) const {
#if LOG_TRACE
	std::cout << "SETTING UNIFORM MATRIX 4 WITH ID " << name << std::endl;
#endif
	glUniformMatrix4fv(glGetUniformLocation(this->shader_id, name), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setUniformVec3(const char* name, const glm::vec3 &vec) const {
	glUniform3f(glGetUniformLocation(this->shader_id, name), 1, GL_FALSE, vec[0]);
};
