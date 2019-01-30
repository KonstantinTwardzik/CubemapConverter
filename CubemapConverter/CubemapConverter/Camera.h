#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


class Camera
{
public:
	Camera(const glm::vec3&pos, float fov, float aspect, float zNear, float zFar) {
		m_position = pos;
		m_forward = glm::vec3(1, 0, 0);
		m_up = glm::vec3(0, 1, 0);
		projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
		viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	inline glm::mat4 GetProjectionMatrix() const {
		return projectionMatrix;
	}

	inline glm::mat4 GetViewMatrix() const {
		return viewMatrix;
	}

	~Camera();

private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

