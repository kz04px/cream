#include <cream/cream.hpp>

class Game : public cream::Engine {
   public:
    Game() {
    }
};

int main(int argc, char **argv) {
    Game game;

    while (game.run()) {
        game.update();
    }

    return 0;
}
