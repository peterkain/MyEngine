#version 330 core

in VS_OUT {
	vec2 uv;
} fs_in;

out vec4 o_color;

uniform float u_texture_size;

uniform sampler2D TextureAtlas;
uniform sampler2D TileData;

const float atlas_size = 16.f;
const float convert = 255.f / atlas_size;
const float atlas_correction = .995f;

void main(void)
{
	float tex_id = texelFetch(TileData, ivec2(fs_in.uv), 0).r * 255.0;
	float y = floor(tex_id / atlas_size);
	float x = tex_id - atlas_size * y;

	// Texture Atlas Lookup
	vec2 tex_coord = vec2(x, atlas_size - 1 - y) / atlas_size + (u_texture_size * atlas_correction) * fract(vec2(fs_in.uv.x, 1.0 - fs_in.uv.y));

	o_color = texture(TextureAtlas, tex_coord);
}