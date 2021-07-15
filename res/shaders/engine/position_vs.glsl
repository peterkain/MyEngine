#version 330 core

layout (location = 0) in vec3 i_position;

uniform mat4 u_projection_view = mat4(1.0);
uniform mat4 u_model = mat4(1.0);

void main(void) 
{
	gl_Position = u_projection_view * u_model * vec4(i_position, 1.0);
}