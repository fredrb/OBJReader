#include "CurveAnimation.h"
#include <cmath>

void CurveAnimation::updatePosition(glm::vec3 &current_position, const glm::vec3 delta, const float timestamp) {
    current_position.x = (float) (radius * cos(timestamp * speed)) + delta.x;
    current_position.y = (float) (radius * sin(timestamp * speed)) + delta.y;
}

CurveAnimation::CurveAnimation(float radius, float speed) : radius(radius), speed(speed) {}

CurveAnimation::CurveAnimation(float radius) : radius(radius), speed(1.0f) {}
