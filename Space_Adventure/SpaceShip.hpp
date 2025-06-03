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
    // The Rule of Five
    SpaceShip(std::string n); // Constructor
    SpaceShip(const SpaceShip& other); // Copy Constructor
    SpaceShip(SpaceShip&& other) noexcept; // Move Constructor
    SpaceShip& operator=(const SpaceShip& other); // Copy Assignment
    SpaceShip& operator=(SpaceShip&& other) noexcept; // Move Assignment Operator
    ~SpaceShip(); // Destructor

    void addWeapon(unique_ptr<Weapon> newWeapon);
    void fireAllWeapons() const;
    string getName() const;
    int getHealth() const;
    const vector<unique_ptr<Weapon>>& getWeapons() const;
    void setHealth(int h);
};