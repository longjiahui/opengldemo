#version 410 core

in vec3 vertexPosition;
uniform mat4 projection;
uniform mat4 transform;

out vec4 position;


void main()
{
    gl_Position = projection * transform * vec4(vertexPosition.xyz, 1.0);
    position = gl_Position;
}