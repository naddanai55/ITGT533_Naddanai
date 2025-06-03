#pragma once
#include <iostream> 
#include "Weapon.hpp"

using namespace std;

class Laser : public Weapon
{
public:
    Laser(int p) : Weapon("Laser", p) {}
    void fire() override 
    {
        cout << "Firing " << getType() << " power: " << getPower() << endl;
    }

    unique_ptr<Weapon> clone() const override 
    {
        return make_unique<Laser>(this->power);
    }
};