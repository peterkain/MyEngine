#pragma once

#include <vector>
#include <unordered_map>
#include "Types.h"
#include "GL/Texture.h"

namespace engine {

class TileMap
{
	std::unordered_map<u8, std::vector<u8>> _layers;
	std::vector<GLuint> _textures;
	std::size_t _w, _h;
	u8 _num_layers;
public:
	TileMap(const char* path, const char delim = ' ');

	void add_layer(const char* path, const char delim = ' ');
	void generate_textures();

	inline std::size_t width() const { return _w; }
	inline std::size_t height() const { return _h; }
	inline u8 num_layers() const { return _num_layers; }

	u8& operator()(u8 layer, std::size_t row, std::size_t col)
	{
		return _layers[layer][row * _h + col];
	}

	const GLuint& operator()(u8 layer) const
	{
		return _textures[layer];
	}

	std::vector<u8>& operator[](std::size_t idx)
	{
		return _layers[idx];
	}
};

}