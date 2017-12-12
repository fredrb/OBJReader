#include "MTLReader.h"
#include <fstream>
#include <sstream>

t_mtl_data MTLReader::get_mtl_data() {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open .MTL file" << std::endl;
        throw 1;
    }

    std::string line;
    t_mtl_data obj;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        if (line.at(0) == 'K') {
            this->process_vector(line, obj);
        } else if (line.substr(0, 6) == "map_Kd") {
            this->process_texture_file(line, obj);
        }
    }

    file.close();

    return obj;
}

void MTLReader::process_vector(std::string line, t_mtl_data &data) {
    std::stringstream stream(line);
    std::string prefix;
    std::getline(stream, prefix, ' ');

    t_mtl_vec3 v;
    stream >> v.x >> v.y >> v.z;

    switch (line.at(1)) {
        case 'd':
            data.kd = v;
            break;
        case 'a':
            data.ka = v;
            break;
        case 's':
            data.ks = v;
            break;
        case 'e':
            data.ke = v;
            break;
        default:break;
    }
}

void MTLReader::process_texture_file(std::string line, t_mtl_data &data) {
    std::stringstream stream(line);
    std::string prefix;
    std::getline(stream, prefix, ' ');

    std::string part;

    stream >> part; //map_Kd
    stream >> part; //path
    data.map_kd = part;
}
