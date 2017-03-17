#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float Left, float Right, float Top, float Bottom, float zNear, float zFar) {
		m_ortho = glm::ortho(Left, Right, Top, Bottom, zNear, zFar); //glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos; // Camera's location in World Space
		m_forward = glm::vec3(0, 0, 1); // Location to look at
		m_up = glm::vec3(0, 1, 0); // Up is (0, 1, 0) to view everything upside down it would be (0, -1, 0)
	}

	inline glm::mat4 GetOrthoViewProjection() const {
		return m_ortho * glm::lookAt(glm::vec3(m_position), glm::vec3(m_forward), glm::vec3(m_up)) * glm::mat4(1.0f);
	}

private:
	glm::mat4 m_ortho;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

