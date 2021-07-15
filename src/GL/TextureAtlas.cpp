#include "GL/TextureAtlas.h"

namespace engine {

TextureAtlas::TextureAtlas(Texture* const atlas, u8 sprite_size, u16 active_textures)
{
	u8 cols{ static_cast<u8>(atlas->width() / sprite_size) };
	u8 rows{ static_cast<u8>(atlas->height() / sprite_size) };
	double offset{ static_cast<double>(sprite_size) / atlas->width() };
	double correction{ (offset / sprite_size) * .2f };

	_size = static_cast<float>(offset);
	_positions.reserve(cols * rows);

	for (u8 r{}; r != rows; r++)
		for (u8 c{}; c != cols; c++)
			_positions.push_back(glm::vec2{ 
			    c / static_cast<float>(sprite_size),
				((rows - 1) - r) / static_cast<float>(sprite_size)
			});
}

}