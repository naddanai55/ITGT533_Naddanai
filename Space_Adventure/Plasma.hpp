#pragma once
#include <iostream> 
#include "Weapon.hpp"

using namespace std;

class Plasma : public Weapon
{
public:
    Plasma(int p) : Weapon("Plasma", p) {}
    void fire() override 
    {
        cout << "Firing " << getType() << " power: " << getPower() << endl;
    }

    unique_ptr<Weapon> clone() const override 
    {
        return make_unique<Plasma>(this->power);
    }
};