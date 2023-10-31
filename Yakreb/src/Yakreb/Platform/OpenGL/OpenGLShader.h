#pragma once

#include "Yakreb/Renderer/Shader.h"

#include <filesystem>

typedef unsigned int GLenum;

namespace Yakreb {

	class OpenGLShader : public Shader {
		public:
			OpenGLShader(const std::string& path);
			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			~OpenGLShader();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void SetFloat(const std::string& name, float value) override;
			virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

			virtual void SetInt(const std::string& name, int value) override;
			virtual void SetInt2(const std::string& name, const glm::ivec2& value) override;
			virtual void SetInt3(const std::string& name, const glm::ivec3& value) override;
			virtual void SetInt4(const std::string& name, const glm::ivec4& value) override;
			virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

			virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
			virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

			virtual void SetBool(const std::string& name, bool value) override;

			virtual const std::string& GetName() const override { return m_Name; }

		private:
			std::string ReadFile(const std::filesystem::path& path);
			std::unordered_map<GLenum, std::string> ProcessFile(const std::string& source);
			void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
			uint32_t m_RendererID;
			std::string m_Name;

	};

}