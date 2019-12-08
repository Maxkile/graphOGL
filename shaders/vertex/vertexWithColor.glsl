#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;

out vec3 outVertexColor;//push further
out vec2 texPos;//push further

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    outVertexColor = color;
    texPos = textureCoords;
}