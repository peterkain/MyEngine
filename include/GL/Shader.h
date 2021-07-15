#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>

#include "Parameters.h"


namespace engine {

struct ShaderData
{
	GLint size;
	GLenum type;

	std::shared_ptr<GLchar> name;
	GLsizei name_length;
};

class Shader 
{
	inline static std::string _prefix{};

	GLuint _id;
	std::unordered_map<std::string, GLint> _locations;

	std::vector<ShaderData> _attributes;
	std::vector<ShaderData> _uniforms;

private:
	GLuint compile(const std::string& path, GLenum shaderType);
	void get_info();
	GLint location(const std::string& name);

public:
	Shader(Parameters<Shader> params);
	// TODO
	// Shader(const char* vsPath, const char* gsPath, const char* fsPath);
	~Shader() noexcept;

	inline const std::vector<ShaderData>& attributes() const { return _attributes; }
	inline const std::vector<ShaderData>& uniforms() const { return _uniforms; }

	inline void use() { glUseProgram(_id); }

	static inline void use_none() { glUseProgram(0); }
	static inline void set_path_prefix(const char* path) { _prefix = path; }

	// -----------------------------------------------
	// Uniform setters
	inline void set_bool(const std::string& name, GLboolean value)
	{
		glUniform1i(location(name), value);
	}

	inline void set_int(const std::string& name, GLint value)
	{
		glUniform1i(location(name), value);
	}

	inline void set_float(const std::string& name, GLfloat value)
	{
		glUniform1f(location(name), value);
	}

	inline void set_float2(const std::string& name, GLfloat x, GLfloat y)
	{
		glUniform2f(location(name), x, y);
	}

	inline void set_float3(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
	{
		glUniform3f(location(name), x, y, z);
	}

	inline void set_float4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		glUniform4f(location(name), x, y, z, w);
	}

	inline void set_vec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(location(name), 1, &value[0]);
	}

	inline void set_vec2(const std::string& name, const glm::ivec2& value)
	{
		glUniform2iv(location(name), 1, &value[0]);
	}

	inline void set_vec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(location(name), 1, &value[0]);
	}

	inline void set_vec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(location(name), 1, &value[0]);
	}

	inline void set_mat2(const std::string& name, const glm::mat2& value)
	{
		glUniformMatrix2fv(location(name), 1, GL_FALSE, &value[0][0]);
	}

	inline void set_mat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(location(name), 1, GL_FALSE, &value[0][0]);
	}

	inline void set_mat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(location(name), 1, GL_FALSE, &value[0][0]);
	}
};

}