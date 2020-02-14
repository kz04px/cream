#ifndef CREAM_TEXTURE_HPP
#define CREAM_TEXTURE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace cream {

class Texture {
   public:
    Texture(const std::string &path);

    ~Texture();

    [[nodiscard]] int width() const noexcept;

    [[nodiscard]] int height() const noexcept;

    void bind() const noexcept;

   private:
    GLuint id_;
    int width_;
    int height_;
    int channels_;
};

}  // namespace cream

#endif
