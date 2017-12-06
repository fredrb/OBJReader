#ifndef OBJREADER_SCENEREADER_H
#define OBJREADER_SCENEREADER_H

#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
    float x, y, z;
} object_target_t;

typedef struct {
    std::string id;
    std::string model_path;
    float x, y, z;
    object_target_t* target = NULL;
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
