#include "GameEngine.hpp" 
#include <iostream>

using namespace std;

int main() 
{
    NP::GameEngine mathGame;
    mathGame.init("game_settings.json", "enemy_level_data.json", "level_select_map.json");
    mathGame.run();
    return 0;
}