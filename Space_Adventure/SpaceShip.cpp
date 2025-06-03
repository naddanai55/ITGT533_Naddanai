#include <iostream> 
#include "SpaceShip.hpp"
#include "Weapon.hpp"

using namespace std;

// Constructor
SpaceShip::SpaceShip(string n) : name(n), health(100) {}

// Copy Constructor
SpaceShip::SpaceShip(const SpaceShip& other) : name(other.name), health(other.health) 
{
    for (const auto& weapon_ptr : other.weapons) 
    {
        if (weapon_ptr) 
        {
            this->weapons.push_back(weapon_ptr->clone());
        }
    }
}

// Move Constructor
SpaceShip::SpaceShip(SpaceShip&& other) noexcept : name(move(other.name)),health(other.health),weapons(move(other.weapons)) 
{
    other.health = 0; // Reset health of the moved-from object
    // other.weapons is now empty
}

// Copy Assignment Operator
SpaceShip& SpaceShip::operator=(const SpaceShip& other) 
{
    if (this == &other) 
    {
        return *this;
    }
    // Copy-and-swap idiom is often preferred, but for direct implementation:
    name = other.name;
    health = other.health;

    // Clear existing weapons and deep copy new ones
    weapons.clear(); // Release existing unique_ptrs
    for (const auto& weapon_ptr : other.weapons) {
        if (weapon_ptr) {
            this->weapons.push_back(weapon_ptr->clone());
        }
    }
    return *this;
}

// Move Assignment Operator
SpaceShip& SpaceShip::operator=(SpaceShip&& other) noexcept {
    if (this == &other) { // Self-assignment check
        return *this;
    }

    name = move(other.name);
    health = other.health;
    weapons = move(other.weapons); // Efficiently move the vector of unique_ptrs

    other.health = 0; // Reset state of the moved-from object
    // other.weapons is now empty

    return *this;
}

// Destructor
SpaceShip::~SpaceShip() {}
    // The unique_ptrs in the 'weapons' vector will automatically delete
    // the Weapon objects they own when the vector is destroyed.
    // So, no explicit cleanup needed here for 'weapons'.



void SpaceShip::addWeapon(std::unique_ptr<Weapon> newWeapon) 
{
    if (newWeapon) 
    {
        cout << "Adding " << newWeapon->getType() << " to " << this->name << endl;
        weapons.push_back(move(newWeapon)); //unique_ptr
    }
}

void SpaceShip::fireAllWeapons() const 
{
    if (weapons.empty()) 
    {
        cout << name << " has no weapons to fire." << endl;
        return;
    }
    cout << name << " firing all weapons:" << endl;
    for (const auto& weapon_ptr : weapons) 
    {
        if (weapon_ptr) 
        {
            weapon_ptr->fire(); // Polymorphic call
        }
    }
}

string SpaceShip::getName() const 
{
    return name;
}

int SpaceShip::getHealth() const 
{
    return health;
}

const vector<unique_ptr<Weapon>>& SpaceShip::getWeapons() const 
{
    return weapons;
}

void SpaceShip::setHealth(int h) 
{
    if (h < 0) h = 0;
    if (h > 100) h = 100; // Assuming 100 is max health
    this->health = h;
}
