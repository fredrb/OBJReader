#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <iostream>
#include <vector>

typedef struct {
	float x, y, z;
} t_vector;

typedef struct {
	float x, y, z;
} t_vector_normal;

typedef struct {
	unsigned int x_position, y_position, z_position;
	unsigned int x_normal, y_normal, z_normal;
} t_face;

typedef struct {
	std::vector<t_vector> vertices;
	std::vector<t_vector_normal> normals;
	std::vector<t_face> faces;
} t_obj_data;

class OBJReader {

private:
	std::string path;

	void process_comment(const std::string line, t_obj_data &data);

	void process_vertex(const std::string line, t_obj_data &data);

	void process_face(const std::string line, t_obj_data &data);

public:
	OBJReader(std::string path) : path(path) {};

	t_obj_data get_obj_data();

};

#endif
