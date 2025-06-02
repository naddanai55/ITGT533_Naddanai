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
        cout << "Firing: " << getType() << endl;
        cout << "Power: " << getPower() << endl;
    }
};