#include "yakrebpch.h"
#include "OpenGLShader.h"

#include "Yakreb/Core/Util/FilesystemHelper.h"

#include <glad/glad.h>

namespace Yakreb {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;

		YGE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		std::filesystem::path filePath = std::filesystem::absolute(FilesystemHelper::GetExecutableDirectoryPath() / (std::filesystem::path(path).make_preferred()));
		std::string source = ReadFile(filePath);
		auto shaderSources = ProcessFile(source);
		Compile(shaderSources);
		m_Name = filePath.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform1i(location, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, const glm::ivec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform2i(location, value.x, value.y);
	}

	void OpenGLShader::SetInt3(const std::string& name, const glm::ivec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform3i(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetInt4(const std::string& name, const glm::ivec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetBool(const std::string& name, bool value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			YGE_CORE_ASSERT(false, "Shader uniform data could not be located!");
			return;
		}
		glUniform1i(location, value);
	}

	std::string OpenGLShader::ReadFile(const std::filesystem::path& path) {
		std::string source;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in) {
			YGE_CORE_ERROR("Could not open file: {}", path.string());
			YGE_CORE_ERROR("Reason: {}", std::strerror(errno));
			YGE_CORE_ASSERT(false, "Could not open file!");
		}
		else if (in) {
			in.seekg(0, std::ios::end);
			source.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&source[0], source.size());
			in.close();
		}
		return source;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ProcessFile(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;
		constexpr const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			YGE_CORE_ASSERT(eol != std::string::npos, "Shader syntax error!");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name
			std::string type = source.substr(begin, eol - begin);
			YGE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after type declaration line
			YGE_CORE_ASSERT(nextLinePos != std::string::npos, "Shader syntax error!");
			pos = source.find(typeToken, nextLinePos); //Start of the next shader type declaration line
			shaderSources[ShaderTypeFromString(type)] =
				(pos == std::string::npos)
				? source.substr(nextLinePos)
				: source.substr(nextLinePos, pos - nextLinePos);
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();
		YGE_CORE_ASSERT(shaderSources.size() <= 2, "Yakreb does not support more than 2 shaders");
		std::array<GLenum, 2> glShaderIDs;
		int index = 0;
		for (auto& kvp : shaderSources) {
			GLenum type = kvp.first;
			const std::string& source = kvp.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = (GLchar*)source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				YGE_CORE_ERROR("{}", "Shader compilation failed!");
				YGE_CORE_ASSERT(false, &(infoLog[0]));

				return;
			}

			glAttachShader(program, shader);
			glShaderIDs[index++] = shader;

		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			YGE_CORE_ERROR("{}", "Shader link failed!");
			YGE_CORE_ASSERT(false, &(infoLog[0]));

			return;
		}

		m_RendererID = program;

		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

}