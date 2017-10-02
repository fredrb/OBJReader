#include "RenderObject.h"

RenderObject::RenderObject(std::string path) {
	OBJReader reader(path);
	raw_data = reader.get_obj_data();
}

void RenderObject::prepare_data() {
	glGenVertexArrays(1, &this->VAO);

	unsigned int VBO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
#if LOG_WARN
	std::cout << "GENERATING BUFFER " << VBO << std::endl << "BINDING VAO: " << VAO << std::endl;
#endif

	this->vertices = std::vector<float>();
	for (auto d : raw_data.vertices) {
		this->vertices.push_back(d.x);
		this->vertices.push_back(d.y);
		this->vertices.push_back(d.z);
	}

	this->indexes = std::vector<unsigned int>();
	for (auto d : raw_data.faces) {
		this->indexes.push_back(d.x_position - 1);
		this->indexes.push_back(d.y_position - 1);
		this->indexes.push_back(d.z_position - 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &indexes.front(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

#if LOG_WARN
	std::cout << "FINISHED BINDING VBO AND EBO" << std::endl;
#endif

	glBindVertexArray(0);
}

void RenderObject::draw() const {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indexes.size(), GL_UNSIGNED_INT, 0);
}
