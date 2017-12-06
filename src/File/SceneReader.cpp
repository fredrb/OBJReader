#include <sstream>
#include "SceneReader.h"

void SceneReader::get_scene_object(std::vector<scene_object_t> &objects) {
    if (!this->file.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        throw 1;
    }

    std::string line;
    bool isReadingObject = false;
    scene_object_t currentObject = scene_object_t();

    while (std::getline(this->file, line)) {
        if (line.empty())
            continue;

        if (isReadingObject) {
            if (line.substr(0,5) == "model") {
                currentObject.model_path = line.substr(6, line.size());
            } else if (line.substr(0,3) == "pos") {
                std::stringstream stream(line.substr(3, line.size()));
                std::string prefix;
                std::getline(stream, prefix, ' ');
                stream >> currentObject.x >> currentObject.y >> currentObject.z;
            } else if (line.substr(0,3) == "end") {
                objects.push_back(currentObject);
                isReadingObject = false;
            } else if (line.substr(0,6) == "target") {
                currentObject.target = new object_target_t();
                std::stringstream stream(line.substr(6, line.size()));
                std::string prefix;
                std::getline(stream, prefix, ' ');
                stream >> currentObject.target->x >> currentObject.target->y >> currentObject.target->z;
            }
        } else if (line.substr(0,5) == "start") {
            currentObject = scene_object_t();
            isReadingObject = true;
            continue;
        }

    }

    this->file.close();
}
