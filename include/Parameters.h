#pragma once

#include <vector>
#include "Types.h"

namespace engine {

	class Shader;
	class Mesh;
	struct Vertex;
	class Texture;

	template<typename T>
	struct Parameters
	{
	};

	template<>
	struct Parameters<Shader>
	{
		const char* vs_path;
		const char* fs_path;
	};

	template<>
	struct Parameters<Mesh>
	{
		std::vector<Vertex> positions;
		std::vector<u32> indices;
	};

	template<>
	struct Parameters<Texture>
	{
		const char* path;
		bool pixelated{ false };
		bool mipmapping{ false };
		GLenum wrap_s{ GL_REPEAT };
		GLenum wrap_t{ wrap_s };
	};

}