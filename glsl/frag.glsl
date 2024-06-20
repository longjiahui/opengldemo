#version 410 core

out vec4 FragColor;
uniform float time;
uniform sampler2D texture1;

in vec4 position;
in vec2 fragTextureCoord;

void main()
{
    float pi = 3.14;
    float r = (sin(time + pi / 4) + 1 )/ 2;
    float g = (sin((time + pi / 2) * 3) + 1 )/ 2;
    float b = (sin((time + pi / 4 * 3) * 2) + 1 )/ 2;
    FragColor = texture(texture1, fragTextureCoord);
}