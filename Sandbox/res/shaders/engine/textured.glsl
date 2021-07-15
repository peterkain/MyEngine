#shadertype vertex
#version 330 core

layout (location = 0) in vec3 i_position;
layout (location = 1) in vec2 i_texcoord;

out vec2 v_texcoord;

uniform mat4 u_model;

void main(void)
{
	gl_Position = u_model * vec4(i_position, 1.0);
	v_texcoord = i_texcoord;
}

#shadertype fragment
#version 330 core

in vec2 v_texcoord;
uniform sampler2D u_texture;

out vec4 o_color;

void main(void)
{
	o_color = texture(u_texture, v_texcoord);
}