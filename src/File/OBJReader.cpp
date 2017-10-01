#include "OBJReader.h"
#include <fstream>
#include <sstream>

void OBJReader::process_comment(const std::string line, t_obj_data &data) {
	
}

void OBJReader::process_vertex(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);	
	std::string prefix;
	std::getline(stream, prefix, ' ');

	float v1, v2, v3;
	stream >> v1 >> v2 >> v3;
	
	data.vertices.push_back(v1);
	data.vertices.push_back(v2);
	data.vertices.push_back(v3);
}

void OBJReader::process_face(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);	
	std::string prefix;
	std::getline(stream, prefix, ' ');

	unsigned int v1, v2, v3;
	stream >> v1 >> v2 >> v3;
	
	data.faces.push_back(v1);
	data.faces.push_back(v2);
	data.faces.push_back(v3);
}

t_obj_data OBJReader::get_obj_data() {

	std::ifstream file(path);

	if (!file.is_open()) {
		std::cout << "Failed to open .OBJ file" << std::endl;
	}	

	std::string line;
	t_obj_data obj;
	while (std::getline(file, line)) {
		if (line.empty()) 
			continue;

		if (line.at(0) == '#') {
			this->process_comment(line, obj);
		} else if (line.at(0) == 'v') {
			this->process_vertex(line, obj);
		} else if (line.at(0) == 'f') {
			this->process_face(line, obj);
		}
	}

	file.close();

	return obj;
}
