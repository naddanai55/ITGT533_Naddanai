#pragma once
#include "Entity.hpp"

namespace CW
{
  class Player :
    public Entity
  {

  public:
    Player();

  private:
    int hp;
    int mp;

  };

}

