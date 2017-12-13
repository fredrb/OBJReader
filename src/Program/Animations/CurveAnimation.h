#ifndef OBJREADER_CURVEANIMATION_H
#define OBJREADER_CURVEANIMATION_H

#include "../../GL/Object/Animation.h"

class CurveAnimation : public Animation {
    float radius;
    float speed;
public:
    void updatePosition(glm::vec3 &current_position, const glm::vec3 delta, const float timestamp) override;

    CurveAnimation(float radius, float speed);
    CurveAnimation(float radius);

};


#endif //OBJREADER_CURVEANIMATION_H
