#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"
#include <stb/stb_image.h>
#include <clog/clog.hpp>

namespace cream {

Texture::Texture(const std::string &path) {
    clog::Log::get()->info("Loading texture from ", path);
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(path.c_str(), &width_, &height_, &channels_, 4);

    if (!data) {
        clog::Log::get()->warn("-- uh oh");
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &id_);
    glTextureStorage2D(id_, 1, GL_RGBA8, width_, height_);

    glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureSubImage2D(id_, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, data);

    clog::Log::get()->info("-- id ", id_);
    clog::Log::get()->info("-- width ", width());
    clog::Log::get()->info("-- height ", height());
    stbi_image_free(data);
}

Texture::~Texture() {
    clog::Log::get()->info("Deleting texture ", id_);
    glDeleteTextures(1, &id_);
}

[[nodiscard]] int Texture::width() const noexcept {
    return width_;
}

[[nodiscard]] int Texture::height() const noexcept {
    return height_;
}

void Texture::bind() const noexcept {
    glBindTexture(GL_TEXTURE_2D, id_);
}

}  // namespace cream
