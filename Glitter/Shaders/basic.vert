#version 330 core

uniform mat4 Transform;
in vec3 Position;
in vec3 ColorIn;

out vec3 Color;

void main()
{
    Color = ColorIn;
    gl_Position = Transform * vec4(Position, 1.0);
}
