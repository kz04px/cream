#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "programs.hpp"
#include "../logging/logging.hpp"

namespace cream
{
    Program::Program()
    {
        program_ = glCreateProgram();
        Logger::get_instance().info("Program created (" + std::to_string(value()) + ")");
    }

    Program::~Program()
    {
        Logger::get_instance().info("Program destroyed (" + std::to_string(value()) + ")");
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
            Logger::get_instance().error("ERROR Program " + std::to_string(program_) + " code " + std::to_string(status));
        }

        return status == GL_TRUE;
    }

    void Program::attach(const Shader &shader)
    {
        auto it = find(shaders_.begin(), shaders_.end(), shader.value());
        if(it == shaders_.end())
        {
            Logger::get_instance().info("Program " + std::to_string(value()) + " attach shader " + std::to_string(shader.value()));
            shaders_.push_back(shader.value());
            glAttachShader(program_, shader.value());
        }
    }

    void Program::detach(const Shader &shader)
    {
        auto it = find(shaders_.begin(), shaders_.end(), shader.value());
        if(it != shaders_.end())
        {
            Logger::get_instance().info("Program " + std::to_string(value()) + " detach shader " + std::to_string(shader.value()));
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
