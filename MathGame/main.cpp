#include "GameEngine.hpp" // This should include all necessary headers transitively for GameEngine
#include <iostream>      // For std::cerr, std::endl

int main() {
    NP::GameEngine mathGame;

    if (!mathGame.init("game_settings.json",
        "enemy_level_data.json",
        "level_select_map.json")) {
        std::cerr << "FATAL: Game initialization failed. Exiting." << std::endl;
        return 1;
    }

    mathGame.run();
    return 0;
}