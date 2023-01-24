#version 330 core

uniform vec3 Mask;
in vec3 Color;
out vec4 ColorOut;

void main()
{
    ColorOut = vec4(Mask, 1.0f) * vec4(Color, 1.0f);
}
