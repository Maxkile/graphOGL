#version 330 core

out vec4 outColor;

uniform vec4 color;

void main()
{
//    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);//RGBA
    outColor = color;
}
