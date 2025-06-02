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
        cout << "Firing: " << getType() << endl;
        cout << "Power: " << getPower() << endl;
    }
};