#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "RenderObject.h"
#include "../../File/OBJReader.h"
#include <GL/glew.h>

typedef struct {
    float x, y, z;
} scene_target_t;

class SceneObject : public RenderObject{

private:
	t_obj_data raw_data;
	unsigned int VAO;
	std::vector<float> vertices;
	std::vector<unsigned int> indexes;
	ShaderProgram* shader_program;
    bool hasTarget;

    scene_target_t* target;
    scene_target_t* currentTarget;
    scene_target_t* initialPosition;

    glm::vec3 position;

    void flipTarget();

	unsigned int texture;
protected:
    glm::mat4 modelMatrix;
public:

	SceneObject(std::string from_path);

    void setTarget(float x, float y, float z);

	void prepare_data() override;

	void draw() const override;

	void attach_shader(std::string source, SHADER_TYPE type) const override;

	void setModelMatrix4(glm::mat4 m) const override;

	void setViewMatrix4(glm::mat4 m) const override;

	void setProjectionMatrix4(glm::mat4 m) const override;

	void setUniformMatrix4(const char* name, glm::mat4 m) const;

	void setUniformVec3(const char* name, glm::vec3 v) const;

	void refresh(glm::mat4 view, glm::mat4 projection) const;

    void setInitialPosition(glm::vec3 position);

    void createModelMatrix();

    void updatePosition();

};

#endif
