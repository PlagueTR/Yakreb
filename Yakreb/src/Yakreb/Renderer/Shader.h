#pragma once

#include <string>
#include <cstdint>
#include <glm/glm.hpp>

namespace Yakreb {

	class Shader : public RefCounted {
		public:
			virtual ~Shader() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void SetFloat(const std::string& name, float value) = 0;
			virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

			virtual void SetInt(const std::string& name, int value) = 0;
			virtual void SetInt2(const std::string& name, const glm::ivec2& value) = 0;
			virtual void SetInt3(const std::string& name, const glm::ivec3& value) = 0;
			virtual void SetInt4(const std::string& name, const glm::ivec4& value) = 0;
			virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

			virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
			virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

			virtual void SetBool(const std::string& name, bool value) = 0;

			virtual const std::string& GetName() const = 0;

			static Ref<Shader> Create(const std::string& path);
			static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		private:
			uint32_t m_RendererID;
	};

}