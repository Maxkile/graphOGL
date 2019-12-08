#version 330 core

in vec3 outVertexColor;
in vec2 texPos;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
//    color = vec4(outVertexColor,1.0f);
    color = texture(ourTexture,texPos) + vec4(outVertexColor,1.0f);//using texture(texPos,texture) func to bind texture to image
}
