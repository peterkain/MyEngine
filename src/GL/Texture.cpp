#include "GL/Texture.h"
#include "GL/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

using namespace std::string_literals;

namespace engine {

Texture::Texture(Parameters<Texture> params)
{
	int channels;

    stbi__vertically_flip_on_load = true;
	stbi_uc* data{ stbi_load(params.path, &_w, &_h, &channels, 0) };

	GLint format{ (channels == 3) ? GL_RGB :
				  (channels == 4) ? GL_RGBA : static_cast<GLuint>(0) };


	if (data == nullptr)
	{
		Logger::log("engine::Texture\n\tFile could not be read. Attempting to load default texture for \n\t"s + params.path,
				        Logger::Level::Warn);

		if (_default_path == "")
			Logger::log("engine::Texture\n\tDefault path for failed texture loading not specified. Aborting...\n",
					        Logger::Level::Error);
		else
		{
			data = stbi_load(_default_path.c_str(), &_w, &_h, &channels, 0);

			if (data == nullptr) Logger::log("Texture default path invalid. Aborting...\n", Logger::Level::Error);
		}

	}

	glGenTextures(1, &_tid);
	glBindTexture(GL_TEXTURE_2D, _tid);

	glTexImage2D(GL_TEXTURE_2D, 0, format, _w, _h, 0, format, GL_UNSIGNED_BYTE, data);

	GLenum min_filter, mag_filter;
	if (params.mipmapping)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		if (params.pixelated)
		{
			min_filter = GL_NEAREST_MIPMAP_NEAREST;
			mag_filter = GL_NEAREST;
		}
		else
		{
			min_filter = GL_LINEAR_MIPMAP_LINEAR;
			mag_filter = GL_LINEAR;
		}
	}
	else
	{
		min_filter = params.pixelated ? GL_NEAREST 
			                          : GL_LINEAR;
		mag_filter = min_filter;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
}


Texture::~Texture()
{
	glDeleteTextures(1, &_tid);
}

}