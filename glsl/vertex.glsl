#version 410 core

in vec3 vertexPosition;
in vec2 textureCoord;
uniform mat4 projection;
uniform mat4 transform;

out vec4 position;
out vec2 fragTextureCoord;


void main()
{
    gl_Position = projection * transform * vec4(vertexPosition.xyz, 1.0);
    position = gl_Position;
    fragTextureCoord = textureCoord;
}