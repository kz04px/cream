#ifndef PROGRAMS_HPP_INCLUDED
#define PROGRAMS_HPP_INCLUDED

#include <vector>
#include "../shaders/shaders.hpp"

namespace cream
{
    class Program
    {
        public:
            Program();
            ~Program();
            void link();
            bool valid() const;
            void attach(const Shader &shader);
            void detach(const Shader &shader);
            void use() const;
            GLuint value() const;
        private:
            GLuint program_;
            std::vector<unsigned int> shaders_;
            bool linked_ = false;
    };
};

#endif
