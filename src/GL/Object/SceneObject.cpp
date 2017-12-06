#include "SceneObject.h"

SceneObject::SceneObject(std::string path) {
	OBJReader reader(path);
	raw_data = reader.get_obj_data();
	this->shader_program = new ShaderProgram();
}

void SceneObject::prepare_data() {
	glGenVertexArrays(1, &this->VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
#if LOG_WARN
	std::cout << "GENERATING BUFFER " << VBO << std::endl << "BINDING VAO: " << VAO << std::endl;
#endif

	this->vertices = std::vector<float>();
	this->indexes = std::vector<unsigned int>();

	for (auto d : raw_data.faces) {
		this->vertices.push_back(raw_data.vertices.at(d.point_index - 1).x);
		this->vertices.push_back(raw_data.vertices.at(d.point_index - 1).y);
		this->vertices.push_back(raw_data.vertices.at(d.point_index - 1).z);

		this->vertices.push_back(raw_data.normals.at(d.normal_index - 1).x);
		this->vertices.push_back(raw_data.normals.at(d.normal_index - 1).y);
		this->vertices.push_back(raw_data.normals.at(d.normal_index - 1).z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#if LOG_WARN
	std::cout << "FINISHED BINDING VBO" << std::endl;
#endif

	glBindVertexArray(0);

	this->shader_program->link_program();
}

void SceneObject::draw() const {
	glBindVertexArray(VAO);
	this->shader_program->use_program();
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 6);
}

void SceneObject::attach_shader(std::string source, SHADER_TYPE type) const {
	shader_program->load_shader_file(source.c_str(), type);
}

void SceneObject::setModelMatrix4(glm::mat4 m) const {
	this->shader_program->use_program();
	shader_program->setUniformMat4("model", m);
}

void SceneObject::setViewMatrix4(glm::mat4 m) const {
	this->shader_program->use_program();
	shader_program->setUniformMat4("view", m);
}

void SceneObject::setProjectionMatrix4(glm::mat4 m) const {
	this->shader_program->use_program();
	shader_program->setUniformMat4("projection", m);
}

void SceneObject::setUniformMatrix4(const char* name, glm::mat4 m) const {
	this->shader_program->use_program();
	shader_program->setUniformMat4(name, m);
};

void SceneObject::setUniformVec3(const char* name, glm::vec3 v) const {
	this->shader_program->use_program();
	shader_program->setUniformVec3(name, v);
}

void SceneObject::updatePosition() {
    if (this->hasTarget) {
        float new_x = this->position.x, new_y = this->position.y, new_z = this->position.z;
        bool x_reached = false, y_reached = false, z_reached = false;

        if ((this->currentTarget->x - this->position.x) < 0.05 && (this->currentTarget->x - this->position.x) > -0.05) {
            x_reached = true;
        } else {
            if (this->currentTarget->x > this->position.x) {
                new_x = static_cast<float>(this->position.x + 0.01);
            } else {
                new_x = static_cast<float>(this->position.x - 0.01);
            }
        }

        if ((this->currentTarget->y - this->position.y) < 0.05 && (this->currentTarget->y - this->position.y) > -0.05) {
            y_reached = true;
        } else {
            if (this->currentTarget->y > this->position.y) {
                new_y = static_cast<float>(this->position.y + 0.01);
            } else {
                new_y = static_cast<float>(this->position.y - 0.01);
            }
        }

        if ((this->currentTarget->z - this->position.z) < 0.05 && (this->currentTarget->z - this->position.z) > -0.05) {
            z_reached = true;
        } else {
            if (this->currentTarget->z > this->position.z) {
                new_z = static_cast<float>(this->position.z + 0.01);
            } else {
                new_z = static_cast<float>(this->position.z - 0.01);
            }
        }

        if (x_reached && y_reached && z_reached)
            this->flipTarget();

        this->position = glm::vec3(new_x, new_y, new_z);
        this->createModelMatrix();
    }
}

void SceneObject::refresh(glm::mat4 view, glm::mat4 projection) const {
    this->setModelMatrix4(this->modelMatrix);
    this->setViewMatrix4(view);
    this->setProjectionMatrix4(projection);
}

void SceneObject::setTarget(float x, float y, float z) {
	this->hasTarget = true;
    auto target = new scene_target_t();
    target->x = x;
    target->y = y;
    target->z = z;
	this->target = target;
    this->currentTarget = target;
}

void SceneObject::createModelMatrix() {
    glm::mat4 model;
    this->modelMatrix = glm::translate(model, this->position);
}

void SceneObject::setInitialPosition(glm::vec3 position) {
    auto target = new scene_target_t();
    target->x = position.x;
    target->y = position.y;
    target->z = position.z;
    this->initialPosition = target;
    this->position = position;
}

void SceneObject::flipTarget() {
    this->currentTarget = (this->currentTarget == this->target) ?
                          this->initialPosition :
                          this->target;
    std::cout << "UPDATING TARGET!" << std::endl;
};
