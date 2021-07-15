#include "TileMap.h"
#include "GL/Logger.h"
#include <fstream>
#include <sstream>

namespace engine {

TileMap::TileMap(const char* path, const char delim) :
	_num_layers{ 0 }
{
	add_layer(path, delim);
}

void TileMap::add_layer(const char* path, const char delim)
{
	std::ifstream file;
	std::stringstream stream;
	std::size_t w{};
	std::size_t h{};

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);

		stream << file.rdbuf();

		file.close();
	}
	catch (std::ifstream::failure& e)
	{
		Logger::log(e.what(), Logger::Level::Error);
	}

	std::string line;
	while (std::getline(stream, line))
	{
		std::istringstream line_stream{ line };
		_layers[_num_layers].reserve(line.size());
		while (std::getline(line_stream, line, delim))
		{
			_layers[_num_layers].push_back(std::stoi(line));
		}
		h++;
	}

	w = _layers[_num_layers].size() / h;

	_w = w;
	_h = h;
	_num_layers++;
}

void TileMap::generate_textures()
{
	_textures.resize(_num_layers);
	glGenTextures(_num_layers, _textures.data());
	for (u8 i{}; i != _num_layers; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _w, _h, 0, GL_RED, GL_UNSIGNED_BYTE, _layers[i].data());
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

}