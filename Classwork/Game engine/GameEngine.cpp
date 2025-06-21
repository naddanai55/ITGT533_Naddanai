#include "GameEngine.hpp"
#include <iostream>

namespace CW
{
  GameEngine::GameEngine() {}
  void GameEngine::init() 
  {
    std::cout << "init game engine." << std::endl;
    map = std::make_unique<Map>();
    player = std::make_unique<Player>();
    // create enemies!
    enemies.push_back(std::make_shared<Enemy>());
    enemies.push_back(std::make_shared<Enemy>());
    enemies.push_back(std::make_shared<Enemy>());

  }

  int GameEngine::handleInput() 
  {
    std::cout << "What do you want to do?" << std::endl;
    std::cout << "a : move left" << std::endl;
    std::cout << "w : move up" << std::endl;
    std::cout << "d : move right" << std::endl;
    std::cout << "s : move down" << std::endl;
    std::cout << "x : exit" << std::endl;
    char input;
    std::cin >> input;
    if (input == 'x')
      return 0;
    else
      return 1;
  }

  void GameEngine::update()
  {
    std::cout << "update game logic" << std::endl;
  }
  
  void GameEngine::render() 
  {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "render." << std::endl;
    map->draw();
    std::cout << static_cast<char>(player->getSymbol());
    
    for (size_t i=0; i < enemies.size(); i++)
    {
      std::cout << static_cast<char>(enemies[i]->getSymbol());
    }
  }
  
  void GameEngine::release() 
  {
    std::cout << "release game." << std::endl;
  }

}
