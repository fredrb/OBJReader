#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <GL/glew.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ShaderProgram.h"
#include "./Animation.h"

class RenderObject {
public:
	virtual void prepare_data() = 0;

	virtual void draw() const = 0;

	virtual void attach_shader(std::string source, SHADER_TYPE type) const = 0;

    virtual void attach_animation(Animation* animation) = 0;

	virtual void setModelMatrix4(glm::mat4 m) const = 0;

	virtual void setViewMatrix4(glm::mat4 m) const = 0;

	virtual void setProjectionMatrix4(glm::mat4 m) const = 0;
};

#endif
