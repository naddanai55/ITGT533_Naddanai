#include "Map.hpp"
#include <iostream>

namespace CW
{

  Map::Map()
  {
    // init a map
    tiles.resize(height, std::vector<char>(width, '.'));
  }

  void Map::draw()
  {
    // draw a map
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      { 
        std::cout << tiles[y][x];
      }
      std::cout << std::endl;
    }
  }

}