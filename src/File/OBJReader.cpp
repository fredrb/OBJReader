#include "OBJReader.h"
#include <fstream>
#include <sstream>

void OBJReader::process_comment(const std::string line, t_obj_data &data) {

}

void OBJReader::process_texture(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);
	std::string prefix;
	std::getline(stream, prefix, ' ');

	t_texture t;
	stream >> t.x >> t.y;

	data.texture.push_back(t);
}

void OBJReader::process_natural(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);
	std::string prefix;
	std::getline(stream, prefix, ' ');

	t_vector_normal v;
	stream >> v.x >> v.y >> v.z;

	std::cout << "Normals read : " << v.x << " " << v.y << " " << v.z << std::endl;

	data.normals.push_back(v);
}

void OBJReader::process_vertex(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);
	std::string prefix;
	std::getline(stream, prefix, ' ');

	t_vector v;
	stream >> v.x >> v.y >> v.z;

	std::cout << "Vertices read : " << v.x << " " << v.y << " " << v.z << std::endl;

	data.vertices.push_back(v);
}

void OBJReader::process_face(const std::string line, t_obj_data &data) {
	std::stringstream stream(line);
	std::string chunk;
	std::getline(stream, chunk, ' ');

	while (std::getline(stream, chunk, ' ')) {
		if (chunk.empty())
			continue;
		t_face f;
		std::istringstream ss(chunk);
		std::string num;
		std::getline(ss, num, '/');
		f.point_index = stoi(num);
		std::getline(ss, num, '/');
		f.texture_index = stoi(num);
		std::getline(ss, num);
		f.normal_index = stoi(num);
		std::cout << "Point: " << f.point_index << "Texture: " << f.texture_index << " Normal: " << f.normal_index << std::endl;
		data.faces.push_back(f);
	}
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
		} else if (line.at(0) == 'v' && line.at(1) == 'n' ) {
			this->process_natural(line,obj);
		} else if (line.at(0) == 'v' && line.at(1) == 't' ) {
			this->process_texture(line, obj);
		} else if (line.at(0) == 'v') {
			this->process_vertex(line, obj);
		} else if (line.at(0) == 'f') {
			this->process_face(line, obj);
		}
	}

	file.close();

	return obj;
}
