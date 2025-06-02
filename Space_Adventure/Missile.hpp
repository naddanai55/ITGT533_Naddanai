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
        cout << "Firing: " << getType() << endl;
        cout << "Power: " << getPower() << endl;
    }
};