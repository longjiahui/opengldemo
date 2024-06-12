#pragma once
#include <string>
#include "glfw.hpp"

namespace huige
{
    class Program
    {
    private:
        unsigned int program;
        unsigned int vertexShader;
        unsigned int fragmentShader;
        std::string vertexSource;
        std::string fragmentSource;

    public:
        Program(const char *, const char *);

        /* 不允许拷贝构造和赋值构造，只允许转移 */
        Program(Program &&);
        Program(Program &) = delete;
        Program &operator=(Program &) = delete;
        ~Program();

        void use();
    };

    class VBO
    {
    private:
        unsigned int instance;

    public:
        std::shared_ptr<std::vector<float>> vertices;
        VBO(std::shared_ptr<std::vector<float>>);
        /* 不允许拷贝构造和赋值构造，只允许转移 */
        VBO(VBO &&);
        VBO(VBO &) = delete;
        VBO &operator=(VBO &) = delete;
        ~VBO();

        void use();
        void useVerteces(std::shared_ptr<std::vector<float>> vertices, GLenum usage = GL_STATIC_DRAW);
    };

    /* Draw Context */
    // class GLDrawContext
    // {
    // private:
    //     std::shared_ptr<GLContext> glContext;
    //     std::shared_ptr<Program> program;
    //     std::shared_ptr<GLVBO> VBO;

    // public:
    //     GLDrawContext(GLContext, std::shared_ptr<Program>, std::shared_ptr<GLVBO>);
    //     void draw();
    // };

    /* A VAO */
    class VAO;
    typedef std::function<void()> VAOUseFunc;

    class VAO
    {
    private:
        unsigned int instance;

    public:
        VAO();

        /* 不允许拷贝构造和赋值构造，只允许转移 */
        VAO(VAO &&);
        VAO(VAO &) = delete;
        VAO &operator=(VAO &) = delete;
        ~VAO();

        void use(VAOUseFunc);

        std::shared_ptr<VBO> createVBO(std::shared_ptr<std::vector<float>> vertices);
        void useVBO(std::shared_ptr<VBO> vbo, GLint interval, GLint index = 0);
        void drawArray(std::shared_ptr<Program>, GLsizei, GLint = 0, GLenum = GL_TRIANGLES);
    };
}