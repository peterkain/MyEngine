#version 330 core

out vec4 o_color;

uniform vec3 u_color = vec3(.6, .2, .6);

void main(void)
{
	o_color = vec4(u_color, 1.0);
}