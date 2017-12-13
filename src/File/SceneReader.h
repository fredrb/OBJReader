#ifndef OBJREADER_SCENEREADER_H
#define OBJREADER_SCENEREADER_H

#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
    std::string id;
    std::string model_path;
    float x, y, z;
    float radius;
    float speed = 0.0f;
} scene_object_t;

class SceneReader {
private:
    std::ifstream file;
public:
    SceneReader(const char* path) : file(std::ifstream(path)) {};
    ~SceneReader() { this->file.close(); }
    void get_scene_object(std::vector<scene_object_t> &objects);
};


#endif //OBJREADER_SCENEREADER_H
