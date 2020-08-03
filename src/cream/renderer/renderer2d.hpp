#ifndef CREAM_RENDERER_RENDERER2D_HPP
#define CREAM_RENDERER_RENDERER2D_HPP

#include <glm/glm.hpp>
#include "../colour.hpp"

namespace cream {

class Camera;

class Renderer2D {
   public:
    static void init();

    static void shutdown();

    static void begin(const Camera &camera);

    static void end();

    static void draw_quad(const glm::vec2 &pos,
                          const glm::vec2 &size,
                          const Colour &c,
                          const int layer = 0);

    static void draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Colour &c);

   private:
    static void flush();
};

}  // namespace cream

#endif
