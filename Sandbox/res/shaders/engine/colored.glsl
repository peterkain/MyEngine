//Colored - no lighting (cnl)
#shadertype vertex
#version 330 core

layout (location = 0) in vec3 i_position;

uniform mat4 u_model = mat4(1.0f);

void main(void)
{
    gl_Position = u_model * vec4(i_position, 1.0);
}


#shadertype fragment
#version 330 core

out vec4 o_color;

uniform vec4 u_color;

void main(void)
{
    o_color = u_color;
}
