#version 330 core

in VS_OUT
{
	vec2 uv;
} fs_in;

out vec4 o_color;

uniform sampler2D u_texture;
uniform vec3 u_color = vec3(1.0, 1.0, 1.0);

void main(void)
{
	o_color = texture(u_texture, fs_in.uv) * vec4(u_color, 1.0);
}