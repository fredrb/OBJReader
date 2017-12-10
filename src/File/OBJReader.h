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
	unsigned int point_index;
	unsigned int normal_index;
	unsigned int texture_index;
} t_face;

typedef struct {
	float x, y;
} t_texture;

typedef struct {
	std::vector<t_vector> vertices;
	std::vector<t_vector_normal> normals;
	std::vector<t_face> faces;
	std::vector<t_texture> texture;
} t_obj_data;

class OBJReader {

private:
	std::string path;

	void process_comment(const std::string line, t_obj_data &data);

	void process_vertex(const std::string line, t_obj_data &data);

	void process_face(const std::string line, t_obj_data &data);

	void process_natural(const std::string line, t_obj_data &data);

	void process_texture(const std::string line, t_obj_data &data);

public:
	OBJReader(std::string path) : path(path) {};

	t_obj_data get_obj_data();

};

#endif
