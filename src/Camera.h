#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
	const float radius = 10.0f;
	const float cameraSpeed = 0.05f;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
public:
	Camera() : cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
						 cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
						 cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {};

	void apply_view(float timestamp, glm::mat4 &view) const;

	void move_up();

	void move_down();

	void move_left();
	
	void move_right();
};

#endif
