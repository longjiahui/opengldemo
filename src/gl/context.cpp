#include "gl/context.hpp"
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <fstream>
#include <string>

using namespace huige;
using namespace std;

GLContext::GLContext()
{
    glGenVertexArrays(1, &this->VAO);
}

void GLContext::useProgram(Program program)
{
}

Program::Program(const char *vertexPath, const char *fragmentPath)
{
    ifstream vertexFile(vertexPath, ios_base::in);
    this->vertexSource = string(istreambuf_iterator<char>(vertexFile), istreambuf_iterator<char>());
    vertexFile.close();
    ifstream fragmentfile(fragmentPath, ios_base::in);
    this->fragmentSource = string(istreambuf_iterator<char>(fragmentfile), istreambuf_iterator<char>());
    fragmentfile.close();

    glShaderSource(this->vertexShader, 1, (const GLchar *const *)this->vertexSource.c_str(), nullptr);
    glShaderSource(this->fragmentShader, 1, (const GLchar *const *)this->fragmentSource.c_str(), nullptr);
    glCompileShader(this->vertexShader);
    glCompileShader(this->fragmentShader);
    this->program = glCreateProgram();
    glAttachShader(this->program, this->vertexShader);
    glAttachShader(this->program, this->fragmentShader);
}

Program::~Program()
{
    glDetachShader(this->program, this->vertexShader);
    glDetachShader(this->program, this->fragmentShader);
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->program);
}