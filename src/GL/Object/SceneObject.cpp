#include "SceneObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

SceneObject::SceneObject(std::string path) {
	OBJReader reader(path);
	raw_data = reader.get_obj_data();
	this->shader_program = new ShaderProgram();
}

void SceneObject::prepare_data() {
    this->shader_program->link_program();

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

		this->vertices.push_back(raw_data.texture.at(d.texture_index -1).x);
		this->vertices.push_back(raw_data.texture.at(d.texture_index -1).y);
	}



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

#if LOG_WARN
	std::cout << "FINISHED BINDING VBO" << std::endl;
#endif

    this->texture = loadTexture(("../assets/model/" + this->raw_data.mtl.map_kd).c_str());
    // this->texture = loadTexture("../assets/model/container2.png");
    this->texture_specular = loadTexture("../assets/model/container2_specular.png");
    this->shader_program->use_program();
    this->shader_program->setTexture("material.diffuse", 0);
    this->shader_program->setTexture("material.specular", 1);

    glBindVertexArray(0);
}

unsigned int SceneObject::loadTexture(char const * path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

static glm::vec3 get_vec_from_k(t_mtl_vec3 data) {
    return glm::vec3(data.x, data.y, data.z);
}

void SceneObject::draw() const {

    this->shader_program->use_program();
    this->setUniformVec3("light.ambient", get_vec_from_k(this->raw_data.mtl.ka));
	this->setUniformVec3("light.diffuse", get_vec_from_k(this->raw_data.mtl.kd));
	this->setUniformVec3("light.specular", get_vec_from_k(this->raw_data.mtl.ks));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture_specular);

	glBindVertexArray(VAO);
	this->shader_program->use_program();
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 8);
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

void SceneObject::setFloat(const char* name, float v) const {
    this->shader_program->use_program();
    shader_program->setFloat(name, v);
};

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
}


