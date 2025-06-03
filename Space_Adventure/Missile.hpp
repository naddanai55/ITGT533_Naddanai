#pragma once
#include <iostream> 
#include "Weapon.hpp"

using namespace std;

class Missile : public Weapon
{
public:
    Missile(int p) : Weapon("Missile", p) {}
    void fire() override 
    {
        cout << "Firing " << getType() << " power: " << getPower() << endl;
    }

    unique_ptr<Weapon> clone() const override 
    {
        return make_unique<Missile>(this->power);
    }
};