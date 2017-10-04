#include "RenderObject.h"

RenderObject::RenderObject(std::string path) {
	OBJReader reader(path);
	raw_data = reader.get_obj_data();
}

void RenderObject::prepare_data() {
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
}

void RenderObject::draw() const {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 6);
}



