#include <iostream>
#include <cassert>
#include "Weapon.hpp"
#include "Plasma.hpp"
#include "Missile.hpp"
#include "Laser.hpp"
#include "SpaceShip.hpp"
#include "Crew.hpp"

using namespace std;

void repairShip(SpaceShip& ship);
SpaceShip cloneShip(const SpaceShip& ship);
void displayStatus(SpaceShip ship);
void upgradeWeapon(Weapon* weapon);

void repairShip(SpaceShip& ship) 
{
    cout << "Attempting to repair ship: " << ship.getName() << endl;
    ship.setHealth(100);
    cout << ship.getName() << " health restored to " << ship.getHealth() << "." << endl;
}

SpaceShip cloneShip(const SpaceShip& originalShip) 
{
    cout << "Cloning ship: " << originalShip.getName() << "..." << endl;
    SpaceShip clonedShip = originalShip;
    cout << "Cloning complete. New ship named: " << clonedShip.getName() << endl;
    return clonedShip;
}

void displayStatus(SpaceShip ship) 
{
    cout << "--- Displaying Ship Status ---" << endl;
    cout << "Ship Name: " << ship.getName() << endl;
    cout << "Health: " << ship.getHealth() << endl;
    cout << "Weapons: " << endl;
    if (ship.getWeapons().empty())
    {
        cout << "  [No Weapons]" << endl;
    }
    else 
    {
        for (const auto& weapon_ptr : ship.getWeapons()) 
        {
            if (weapon_ptr) 
            {
                cout << "  - Type: " << weapon_ptr->getType() << ", Power: " << weapon_ptr->getPower() << endl;
            }
        }
    }
    cout << "--- End of Status ---" << endl;
}

void upgradeWeapon(Weapon* weaponPtr) 
{
    if (weaponPtr) 
    {
        cout << "Upgrading weapon: " << weaponPtr->getType() << " (Current Power: " << weaponPtr->getPower() << ")" << endl;
        weaponPtr->setPower(weaponPtr->getPower() + 10);
        cout << weaponPtr->getType() << " upgraded. New Power: " << weaponPtr->getPower() << "." << endl;
    }
    else 
    {
        cout << "Attempted to upgrade a null weapon pointer. No action taken." << endl;
    }
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SpaceShip myShip("Nai1 ship");
    cout << myShip.getName() << endl;
    myShip.addWeapon(make_unique<Laser>(15));
    myShip.addWeapon(make_unique<Plasma>(30));
    myShip.addWeapon(make_unique<Missile>(75));
    myShip.fireAllWeapons();
    displayStatus(myShip);
    cout << "------------------------------" << endl;
	Crew crewMember("Pilot", make_shared<SpaceShip>(myShip));
	crewMember.displayInfo();


    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}