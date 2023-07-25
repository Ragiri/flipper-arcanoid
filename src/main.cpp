#include "../includes/Common/game_loop.hpp"

int main() {
    game_loop gl(1000, 1000);

    gl.loop();

    return 0;
}