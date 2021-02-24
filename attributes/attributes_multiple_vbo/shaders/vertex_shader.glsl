#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 color_frag;


void main()
{
    color_frag = color;
    gl_Position = position;
}
