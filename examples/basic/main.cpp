#include <cream/cream.hpp>
#include "layer.hpp"

class Game : public cream::Engine {
   public:
    Game() {
        set_clear_colour(cream::Colour::sky_blue());
        push_layer(new GameLayer());
    }
};

int main(int argc, char **argv) {
    Game game;

    while (game.run()) {
        game.update();
    }

    return 0;
}
