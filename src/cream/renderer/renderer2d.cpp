#include "renderer2d.hpp"
#include <array>
#include <clog/clog.hpp>
#include <cstddef>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "../camera/camera.hpp"
#include "../programs/programs.hpp"
#include "../shaders/shaders.hpp"

namespace cream {

struct VertexData {
    glm::vec3 position;
    Colour colour;
};

struct Statistics {
    unsigned int draw_calls = 0;
    unsigned int draw_triangles = 0;
};

struct Asd {
    Asd() {
        clog::Log::get()->info("Asd");

        // Program
        auto vs = Shader::from_string(ShaderType::VERTEX_SHADER,
                                      "#version 430                                  \n"
                                      "                                              \n"
                                      "layout(location = 0) uniform mat4 view;       \n"
                                      "                                              \n"
                                      "layout(location = 0) in vec3 vertices;        \n"
                                      "layout(location = 1) in vec3 colour;          \n"
                                      "                                              \n"
                                      "layout(location = 0) out vec4 out_weow;       \n"
                                      "                                              \n"
                                      "void main() {                                 \n"
                                      "    gl_Position = view * vec4(vertices, 1.0); \n"
                                      "    out_weow = vec4(colour, 1.0);             \n"
                                      "}                                               ");

        auto fs = Shader::from_string(ShaderType::FRAGMENT_SHADER,
                                      "#version 430                             \n"
                                      "                                         \n"
                                      "layout(location = 0) in vec4 out_weow;   \n"
                                      "                                         \n"
                                      "layout(location = 0) out vec4 FragColor; \n"
                                      "                                         \n"
                                      "void main() {                            \n"
                                      "    FragColor = out_weow;                \n"
                                      "}                                          ");

        program.attach(vs);
        program.attach(fs);
        program.link();
        program.detach(vs);
        program.detach(fs);

        program.use();

        // VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // VBO
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(VertexData),
                              reinterpret_cast<GLvoid *>(offsetof(VertexData, position)));

        // Colours
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(VertexData),
                              reinterpret_cast<GLvoid *>(offsetof(VertexData, colour)));
    }

    ~Asd() {
        clog::Log::get()->info("~Asd");

        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    Program program;
    GLuint vao;
    GLuint vbo;
    Statistics m_statistics;
    constexpr static int max_buffer_size = 128;
    int buffer_index = 0;
    std::array<VertexData, max_buffer_size> m_data;
};

constexpr const std::array<glm::vec3, 6> quad_vertices = {{
    // Triangle 1
    {-0.5f, -0.5f, 0.0f},  // p0
    {-0.5f, 0.5f, 0.0f},   // p1
    {0.5f, 0.5f, 0.0f},    // p2
    // Triangle 2
    {-0.5f, -0.5f, 0.0f},  // p0
    {0.5f, 0.5f, 0.0f},    // p2
    {0.5f, -0.5f, 0.0f},   // p3
}};
static std::unique_ptr<Asd> weow;

void Renderer2D::init() {
    clog::Log::get()->info("Renderer2D::init()");
    weow = std::unique_ptr<Asd>(new Asd());
}

void Renderer2D::shutdown() {
    clog::Log::get()->info("Renderer2D::shutdown()");
    weow.reset();
}

void Renderer2D::begin(const Camera &camera) {
    weow->buffer_index = 0;
    weow->m_statistics.draw_calls = 0;
    weow->m_statistics.draw_triangles = 0;

    weow->program.use();
    const auto view = camera.matrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer2D::end() {
    flush();
}

void Renderer2D::flush() {
    if (weow->buffer_index == 0) {
        return;
    }

#ifndef NDEBUG
    if (weow->buffer_index > weow->max_buffer_size) {
        clog::Log::get()->fatal("buffer_index > max_buffer_size");
        weow->buffer_index = 0;
        return;
    }
#endif

    // Statistics
    weow->m_statistics.draw_calls++;
    weow->m_statistics.draw_triangles += weow->buffer_index / 3;

    // Bind
    glBindVertexArray(weow->vao);

    // Buffer
    glBindBuffer(GL_ARRAY_BUFFER, weow->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 weow->buffer_index * sizeof(weow->m_data[0]),
                 weow->m_data.data(),
                 GL_STATIC_DRAW);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, weow->buffer_index);

    // Reset
    weow->buffer_index = 0;
}

void Renderer2D::draw_quad(const glm::vec2 &pos,
                           const glm::vec2 &size,
                           const Colour &c,
                           const int layer) {
    draw_quad({pos.x, pos.y, static_cast<float>(layer)}, size, c);
}

void Renderer2D::draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Colour &c) {
    if (weow->buffer_index + 6 > weow->max_buffer_size) {
        flush();
    }

    for (const auto &n : quad_vertices) {
        weow->m_data[weow->buffer_index].position = pos + n;
        weow->m_data[weow->buffer_index].colour = c;
        weow->buffer_index++;
    }
}

}  // namespace cream
