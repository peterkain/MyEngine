#pragma once
#include "GL/Texture.h"
#include "Types.h"
#include <glm/glm.hpp>

namespace engine {

class TextureAtlas
{
	std::vector<glm::vec2> _positions;
	float _size;
public:
	TextureAtlas(Texture* const atlas, u8 sprite_size, u16 active_textures = 0);

	inline const glm::vec2& const position(u8 idx) const { return _positions[idx]; }
	inline const float& size() const { return _size; }
	inline std::size_t textures() const { return _positions.size(); }
};

}