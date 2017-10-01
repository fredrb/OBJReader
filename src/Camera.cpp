#include "Camera.h"

void Camera::apply_view(float timestamp, glm::mat4 &mat) const {
/*
	float cam_x = sin(timestamp) * radius;
	float cam_z = cos(timestamp) * radius;
	mat = glm::lookAt(glm::vec3(cam_x, 0.0f, cam_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
*/
	mat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::move_up() {
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::move_down() {
	cameraPos -= cameraSpeed * cameraFront; 
}

void Camera::move_left() {
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::move_right() {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

