#include <iostream>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "programs.hpp"

namespace cream
{
    Program::Program()
    {
        program_ = glCreateProgram();
    }

    Program::~Program()
    {
        glDeleteProgram(program_);
    }

    void Program::link()
    {
        glLinkProgram(program_);

        for(auto &s : shaders_)
        {
           glDetachShader(program_, s);
        }

        linked_ = true;
    }

    bool Program::valid() const
    {
    	GLint status;
        glGetProgramiv(program_, GL_LINK_STATUS, &status);

        if(status == GL_FALSE)
        {
            std::cout << "ERROR Program " + std::to_string(program_) + " code " + std::to_string(status) << std::endl;
        }

        return status == GL_TRUE;
    }

    void Program::attach(const Shader &shader)
    {
        auto it = find(shaders_.begin(), shaders_.end(), shader.value());
        if(it == shaders_.end())
        {
            shaders_.push_back(shader.value());
            glAttachShader(program_, shader.value());
        }
    }

    void Program::detach(const Shader &shader)
    {
        auto it = find(shaders_.begin(), shaders_.end(), shader.value());
        if(it != shaders_.end())
        {
            shaders_.erase(it);
            glDetachShader(program_, shader.value());
        }
    }

    void Program::use() const
    {
        if(linked_)
        {
            glUseProgram(program_);
        }
    }

    GLuint Program::value() const
    {
        return program_;
    }
}
