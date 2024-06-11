#pragma once
#include <string>

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
        ~Program();
    };

    /* A VAO */
    class GLContext
    {
    private:
        unsigned int VAO;

    public:
        GLContext();
        void useProgram(Program);
    };

}