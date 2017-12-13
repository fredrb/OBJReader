#ifndef OBJREADER_ANIMATION_H
#define OBJREADER_ANIMATION_H

#include <glm/vec3.hpp>

class Animation {
public:
    virtual void updatePosition(glm::vec3 &current_position, const glm::vec3 delta, const float timestamp) = 0;
};

#endif //OBJREADER_ANIMATION_H
