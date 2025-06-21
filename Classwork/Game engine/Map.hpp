#pragma once
#include <vector>

namespace CW
{
  class Map
  {
  public:
    Map();
    void draw();

  private:
    const unsigned int width = 20;
    const unsigned int height = 20;
    std::vector<std::vector<char>>tiles;

  };



}
