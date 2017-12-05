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

void SceneObject::refresh(glm::mat4 view, glm::mat4 projection) const {
    this->setModelMatrix4(this->modelMatrix);
    this->setViewMatrix4(view);
    this->setProjectionMatrix4(projection);
};
