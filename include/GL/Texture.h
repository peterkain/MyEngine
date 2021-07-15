#pragma once

#include <string>
#include <GL/glew.h>

#include "Parameters.h"

namespace engine {

class ResourceManager;

class Texture
{
public:
	Texture(Parameters<Texture> params);
	~Texture();

public:
	inline GLuint id() const { return _tid; }
	inline static void set_defaults(const std::string& default_path)
	{ 
		_default_path = default_path;
	}

	inline int width() const { return _w; }
	inline int height() const { return _h; }

private:
	GLuint _tid;
	int _w, _h;
	inline static std::string _default_path{ "" };
};

}