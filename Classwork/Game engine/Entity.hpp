#pragma once

namespace CW
{
  class Entity
  {
  protected:
    int posX;
    int posY;
    char symbol;

  public:
    Entity();
    Entity(int x, int y, char symbol);
    int getX() const;
    int getY() const;
    int getSymbol() const;
  };

}

