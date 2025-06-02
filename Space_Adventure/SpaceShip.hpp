#pragma once
#include <iostream>
#include <vector>
#include "Weapon.hpp"

using namespace std;

class SpaceShip
{
    string name;
    int health;
    vector<unique_ptr<Weapon>> weapons;

public:
    SpaceShip(string n) : name(n), health(100) {}
    void addWeapon(unique_ptr<Weapon> newWeapon) 
    {
        weapons.push_back(move(newWeapon));
    }

    void fireAllWeapons() 
    {
        cout << name << " firing all weapons: " << endl;
        for (const auto& weapon : weapons)
        {
            if (weapon)
            { 
                weapon->fire();
            }
        }
    }

    string getName() const 
    {
        return name; 
    }

    int getHealth() const 
    { 
        return health; 
    }
};