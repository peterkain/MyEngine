#include "GL/Shader.h"
#include "GL/Logger.h"
#include <fstream>
#include <sstream>

using namespace std::string_literals;

namespace engine {

Shader::Shader(Parameters<Shader> params)
	: _id{ glCreateProgram() }
{
	GLuint vs_id{ compile(_prefix + params.vs_path, GL_VERTEX_SHADER) };
	GLuint fs_id{ compile(_prefix + params.fs_path, GL_FRAGMENT_SHADER) };

	glAttachShader(_id, vs_id);
	glAttachShader(_id, fs_id);

	glLinkProgram(_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	GLint success;
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

		std::string log;
		log.resize(length);
		glGetProgramInfoLog(_id, length, nullptr, log.data());

		Logger::log(log, Logger::Level::Error);
	}
#ifdef _ENGINE_DEBUG
	else
	{
		Logger::log("("s + params.vs_path + ", " + params.fs_path + ") linked successfully", Logger::Level::Debug);
	}
#endif
}


Shader::~Shader() noexcept
{
	glDeleteProgram(_id);
}


void Shader::get_info()
{
	static constexpr GLsizei bufsize{ 16 };
	GLint count;

	glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &count);
	_attributes.resize(count);
	for (GLuint i{}; i != count; i++)
	{
		glGetActiveAttrib(_id, i, bufsize, &_attributes[i].name_length,
			&_attributes[i].size, &_attributes[i].type, _attributes[i].name.get());
	}

	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);
	_uniforms.resize(count);
	for (GLuint i{}; i != count; i++)
	{
		glGetActiveUniform(_id, i, bufsize, &_uniforms[i].name_length,
			&_uniforms[i].size, &_uniforms[i].type, _uniforms[i].name.get());
	}
}


GLint Shader::location(const std::string& name)
{
	auto iter{ _locations.find(name) };
	if (iter == _locations.end()) {
		GLint location{ glGetUniformLocation(_id, name.c_str()) };
		_locations.emplace(name, location);
		return location;
	}

	return iter->second;
}


GLuint Shader::compile(const std::string& path, GLenum shaderType)
{
	std::ifstream file;
	std::stringstream stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		file.open(path);
		stream << file.rdbuf();
		file.close();
	}
	catch (std::ifstream::failure& e)
	{
		Logger::log(e.what(), Logger::Level::Warn);
		Logger::log("Failed to read Shader File: "s + path, Logger::Level::Error);
	}

	const std::string& tmp{ stream.str() };
	const GLchar* code{ tmp.c_str() };

	GLuint id{ glCreateShader(shaderType) };
	glShaderSource(id, 1, &code, nullptr);
	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		std::string log;
		log.resize(length);
		glGetShaderInfoLog(id, length, nullptr, log.data());

		Logger::log(log, Logger::Level::Error);
	}
#ifdef _ENGINE_DEBUG
	else
	{
		Logger::log(path + " compiled successfully"s, Logger::Level::Debug);
	}
#endif

	return id;
}

}