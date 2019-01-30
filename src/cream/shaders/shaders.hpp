#ifndef SHADERS_HPP_INCLUDED
#define SHADERS_HPP_INCLUDED

#include <string>

namespace cream
{
    enum ShaderType
    {
        VERTEX_SHADER = 0,
        FRAGMENT_SHADER
    };

    class Shader
    {
        public:
            Shader();
            ~Shader();
            void load_text(const ShaderType &type, const std::string &text);
            void load_file(const ShaderType &type, const std::string &path);
            GLuint value() const;
            bool valid() const;
        private:
            ShaderType type_;
            unsigned int value_;
    };
};

#endif
