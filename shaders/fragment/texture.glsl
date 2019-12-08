#version 330 core

in vec3 outVertexColor;
in vec2 texPos;

out vec4 color;

uniform sampler2D textureBase;
uniform sampler2D textureSub;

//uniform float alpha;

void main()
{
    color = mix(texture(textureBase,texPos),texture(textureSub,texPos),0.65f);
}
