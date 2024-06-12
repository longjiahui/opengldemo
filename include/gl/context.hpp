#pragma once
#include <string>
#include "glfw.hpp"

namespace huige
{
    class VAO;
    class VBO;

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
        VBO();

    public:
        static std::shared_ptr<VBO> create(VAO const &, std::shared_ptr<std::vector<float>>);
        std::shared_ptr<std::vector<float>> vertices;
        /* 不允许拷贝构造和赋值构造，只允许转移 */
        VBO(VBO &&);
        VBO(VBO &) = delete;
        VBO &operator=(VBO &) = delete;
        ~VBO();

        void use();
        void init(std::shared_ptr<std::vector<float>> vertices, GLenum usage = GL_STATIC_DRAW);
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

        void init();

        void use(VAOUseFunc) const;

        std::shared_ptr<VBO> createVBO(std::shared_ptr<std::vector<float>> vertices);
        void useVBO(std::shared_ptr<VBO> vbo, GLint interval, GLint index = 0);
        void drawArray(std::shared_ptr<Program>, GLsizei, GLint = 0, GLenum = GL_TRIANGLES);
    };
}