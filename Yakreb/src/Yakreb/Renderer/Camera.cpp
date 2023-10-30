#include "yakrebpch.h"
#include "Camera.h"

namespace Yakreb {

	OrthographicCamera::OrthographicCamera() : m_Left(-1.0f), m_Right(1.0f), m_Bottom(-1.0f), m_Top(1.0f) {
		m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateProjectionMatrix() {
		glm::vec4 bounds = glm::vec4(m_Left, m_Right, m_Bottom, m_Top) * (glm::vec4(m_Zoom) / glm::vec4(1.0f));
		m_ProjectionMatrix = glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, -1.0f, 1.0f);
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}