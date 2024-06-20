#version 410 core

out vec4 FragColor;
uniform float time;

in vec4 position;

void main()
{
    float pi = 3.14;
    float r = (sin(time + pi / 4) + 1 )/ 2;
    float g = (sin((time + pi / 2) * 3) + 1 )/ 2;
    float b = (sin((time + pi / 4 * 3) * 2) + 1 )/ 2;
    FragColor = vec4(normalize(position.xyz) * 0.5f + vec3(r, g, b) * 0.5f, 1.0f);
}