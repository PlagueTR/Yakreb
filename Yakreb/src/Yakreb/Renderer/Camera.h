#pragma once

#include <glm/glm.hpp>

namespace Yakreb {

	class Camera {
		public:
			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

			float GetZoom() const { return m_Zoom; }
			void SetZoom(float zoom) { m_Zoom = zoom; RecalculateProjectionMatrix(); RecalculateViewMatrix(); }

			const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		protected:
			virtual void RecalculateProjectionMatrix() = 0;
			virtual void RecalculateViewMatrix() = 0;

			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix;

			glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

			float m_Zoom = 1.0f;

	};

	class OrthographicCamera : public Camera {
		public:
			OrthographicCamera();
			OrthographicCamera(float left, float right, float bottom, float top);

			float GetRotation() const { return m_Rotation; }
			void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		protected:
			virtual void RecalculateProjectionMatrix() override;
			virtual void RecalculateViewMatrix() override;

			float m_Rotation = 0.0f;

			float m_Left, m_Right, m_Bottom, m_Top;

	};

}