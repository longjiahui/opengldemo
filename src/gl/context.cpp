#include "gl/context.hpp"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace huige;
using namespace std;

VAO::VAO()
{
}
void VAO::init()
{
    glGenVertexArrays(1, &(this->instance));
}
VAO::~VAO()
{
    glDeleteVertexArrays(1, &this->instance);
}

shared_ptr<VBO> VAO::createVBO(shared_ptr<vector<float>> vertices)
{
    return VBO::create(*this, vertices);
}
void VAO::use(VAOUseFunc func) const
{
    glBindVertexArray(this->instance);
    func();
}

void VAO::useVBO(shared_ptr<VBO> vbo, GLint interval, GLint index)
{
    this->use(([&]()
               { vbo->use();
        glVertexAttribPointer(index, interval, GL_FLOAT, GL_FALSE, interval * sizeof(float), nullptr);
        glEnableVertexAttribArray(index); }));
}

void VAO::drawArray(shared_ptr<Program> program, GLsizei size, GLint offset, GLenum mode)
{
    this->use([&]()
              {
        program->use();
        glDrawArrays(mode, offset, size); });
}

VBO::VBO()
{
    glGenBuffers(1, &this->instance);
}
shared_ptr<VBO> VBO::create(VAO const &vao, std::shared_ptr<std::vector<float>> vertices)
{
    // auto vbo = make_shared<VBO>();
    shared_ptr<VBO> vbo = shared_ptr<VBO>(new VBO());
    vao.use([&]()
            { vbo->init(vertices); });
    return vbo;
}

void VBO::use()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->instance);
}
void VBO::init(shared_ptr<vector<float>> vertices, GLenum usage)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->instance);
    cout << "vertices size: " << vertices->size() * sizeof(float) << endl;
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_STATIC_DRAW);
    this->vertices = vertices;
}

VBO::~VBO()
{
    glDeleteBuffers(1, &this->instance);
}

Program::Program(Program &&program)
{
    this->program = program.program;
    this->vertexShader = program.vertexShader;
    this->fragmentShader = program.fragmentShader;
    this->vertexSource = program.vertexSource;
    this->fragmentSource = program.fragmentSource;
    program.program = 0;
    program.vertexShader = 0;
    program.fragmentShader = 0;
    program.vertexSource = nullptr;
    program.fragmentSource = nullptr;
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

void Program::use()
{
    glUseProgram(this->program);
}