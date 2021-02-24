#version 330 core

// Input value received from vertex shader
in vec4 position_frag;

out vec4 FragColor;

void main()
{
    FragColor = position_frag;
}
