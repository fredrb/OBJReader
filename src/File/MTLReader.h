#ifndef OBJREADER_MTLREADER_H
#define OBJREADER_MTLREADER_H

#include <iostream>

typedef struct {
    float x, y, z;
} t_mtl_vec3;

typedef struct {
    t_mtl_vec3 kd, ka, ks, ke;
    std::string map_kd;
} t_mtl_data;


class MTLReader {
private:
    std::string path;
public:
    MTLReader (std::string path) : path(path) {};

    t_mtl_data get_mtl_data();

    void process_vector(std::string basic_string, t_mtl_data &param);

    void process_texture_file(std::string line, t_mtl_data &data);
};

#endif
