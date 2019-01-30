#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders.hpp"
#include "../utilities/utilities.hpp"

namespace cream
{
    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
        glDeleteShader(value_);
    }

    void Shader::load_text(const ShaderType &type, const std::string &text)
    {
        assert(type == ShaderType::VERTEX_SHADER || type == ShaderType::FRAGMENT_SHADER);

        switch(type)
        {
            case ShaderType::VERTEX_SHADER:
                value_ = glCreateShader(GL_VERTEX_SHADER);
                break;
            case ShaderType::FRAGMENT_SHADER:
                value_ = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                assert(false);
                break;
        }

        const char *source = text.c_str();
        int length = text.size();
        type_ = type;
        glShaderSource(value_, 1, &source, &length);
        glCompileShader(value_);
    }

    void Shader::load_file(const ShaderType &type, const std::string &path)
    {
        assert(type == ShaderType::VERTEX_SHADER || type == ShaderType::FRAGMENT_SHADER);

        std::ifstream t(path);

        if(!t.is_open())
        {
            return;
        }

        std::stringstream buffer;
        buffer << t.rdbuf();

        load_text(type, buffer.str());
    }

    GLuint Shader::value() const
    {
        return value_;
    }

    bool Shader::valid() const
    {
        GLint status;
        glGetShaderiv(value_, GL_COMPILE_STATUS, &status);

        if(status == GL_FALSE)
        {
            //log("ERROR Shader " + std::to_string(shader) + " code " + std::to_string(status));
        }

        return status == GL_TRUE;
    }
}
