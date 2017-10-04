#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "RenderObject.h"
#include "../../File/OBJReader.h"
#include <GL/glew.h>

class SceneObject : public RenderObject{

private:
	t_obj_data raw_data;
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
	ShaderProgram* shader_program;
public:
	SceneObject(std::string from_path);

	void prepare_data() override;

	void draw() const override;

	void attach_shader(std::string source, SHADER_TYPE type) const override;

	void setModelMatrix4(glm::mat4 m) const override;

	void setViewMatrix4(glm::mat4 m) const override;

	void setProjectionMatrix4(glm::mat4 m) const override;

};

#endif
