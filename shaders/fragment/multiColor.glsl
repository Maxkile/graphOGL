#version 330 core

in vec3 outVertexColor;

out vec4 color;

void main()
{
    color = vec4(outVertexColor,1.0f);
}
