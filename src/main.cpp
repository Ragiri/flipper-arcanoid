#include "../includes/game_loop.hpp"

int main() {
    game_loop gl(1000, 1000);

    gl.parse_map("map");
    gl.print_vect();
    gl.createWindow();
    gl.loop();
    return 0;
}