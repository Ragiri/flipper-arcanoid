#include "../includes/game_loop.hpp"

int main() {
    std::srand(std::time(0));
    game_loop gl(1200, 1080);

    gl.createWindow();
    gl.loop();
    return 0;
}