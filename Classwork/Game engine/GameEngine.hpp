#pragma once
#include <memory>
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

namespace CW
{
  class GameEngine
  {
  public:
    GameEngine();
    void init();
    int handleInput();
    void update();
    void render();
    void release();

  private:
    std::unique_ptr<Map> map;
    std::unique_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
  };

}

