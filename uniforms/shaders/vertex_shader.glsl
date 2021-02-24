#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 R;

void main()
{
    gl_Position = R*position;
}
