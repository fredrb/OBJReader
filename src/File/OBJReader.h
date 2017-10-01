#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <iostream>
#include <vector>

typedef struct {
	std::vector<float> vertices;
	std::vector<unsigned int> faces;
} t_obj_data;

class OBJReader {

private:
	std::string path;

public:
	OBJReader(std::string path) : path(path) {};

	t_obj_data get_obj_data();

	void process_comment(const std::string line, t_obj_data &data); 

	void process_vertex(const std::string line, t_obj_data &data);

	void process_face(const std::string line, t_obj_data &data);
};

#endif
