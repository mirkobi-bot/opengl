#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 textcoord;

out vec2 frag_textcoord;

void main()
{
    frag_textcoord = textcoord;
    gl_Position = vec4(position, 1.0);
}