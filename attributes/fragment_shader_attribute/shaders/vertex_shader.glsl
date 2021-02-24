#version 330 core

// This value is received from the VBO data
layout (location = 0) in vec4 position;

// This value will be passed to the fragment shader
out vec4 position_frag;

uniform mat4 R;
void main()
{
    position_frag = position;
    gl_Position = R*position;
}
