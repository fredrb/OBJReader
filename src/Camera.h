#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
	const float radius = 10.0f;
	const float cameraSpeed = 0.05f;

	bool firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 800.0f / 2;
	float lastY = 600.0f / 2;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
public:
	float fov = 45.0f;

	glm::vec3 cameraPos;

	Camera() : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
						 cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
						 cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)) {};

	void apply_view(float timestamp, glm::mat4 &view) const;

	void move_up();

	void move_down();

	void move_left();

	void move_right();

	void move_mouse(double xpos, double ypos);
};

#endif
