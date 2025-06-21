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
    string clonedName = originalShip.getName() + " (Clone)";
    SpaceShip clonedShip(clonedName);
    clonedShip.setHealth(originalShip.getHealth());
    for (const auto& weapon_ptr : originalShip.getWeapons()) 
    {
        if (weapon_ptr) 
        {
            clonedShip.addWeapon(weapon_ptr->clone());
        }
    }
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
    cout << "-------- End of Status --------" << endl;
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

    //SpaceShip myShip("Nai-SpaceShip");
    //shared_ptr<SpaceShip> mySharedShip = make_shared<SpaceShip>(myShip);

    auto mySharedShip = make_shared<SpaceShip>("myShip");

    cout << "----------- START -----------" << endl;
    cout << "Ship name: " << mySharedShip->getName() << endl;
    mySharedShip->addWeapon(make_unique<Laser>(15));
	mySharedShip->addWeapon(make_unique<Plasma>(30));
	mySharedShip->addWeapon(make_unique<Missile>(75));
    mySharedShip->fireAllWeapons();
    displayStatus(*mySharedShip);
    cout << "!!! " << mySharedShip->getName() << " Get Damage" << endl;
    mySharedShip->setHealth(50);
    displayStatus(*mySharedShip);
    repairShip(*mySharedShip);
    cout << "------------------------------" << endl;

    SpaceShip cloned = cloneShip(*mySharedShip);
    shared_ptr<SpaceShip> clonedShip = make_shared<SpaceShip>(cloned);

    cout << "Status of " << mySharedShip->getName() << endl;
    displayStatus(*mySharedShip);
    cout << "Status of " << clonedShip->getName() << endl;
    displayStatus(*clonedShip);
    cout << "!!! " << clonedShip->getName() << " Get Damage" << endl;
    clonedShip->setHealth(20);
    displayStatus(*mySharedShip);
    displayStatus(*clonedShip);
    clonedShip->addWeapon(make_unique<Laser>(5));
    displayStatus(*mySharedShip);
    displayStatus(*clonedShip);
    cout << "------------------------------" << endl;
    Weapon* weaponToUpgrade = mySharedShip->getWeapons()[0].get();
    upgradeWeapon(weaponToUpgrade);
    displayStatus(*mySharedShip);
    Weapon* clonedWeaponToUpgrade = clonedShip->getWeapons()[1].get();
    upgradeWeapon(clonedWeaponToUpgrade);
    displayStatus(*clonedShip);
    Crew crewPilot("Pilot", mySharedShip);
    crewPilot.displayInfo();
    Crew crewCaptain("Captain", mySharedShip);
    crewCaptain.displayInfo();
    Crew crewEngineer("Engineer", mySharedShip);
    crewEngineer.displayInfo();
    cout << "All primary crew assigned to '" << mySharedShip->getName() << "'. Final ref count: " << mySharedShip.use_count() << endl;
    cout << "(Should be 1 from main + 3 from crew = 4)" << endl;
    cout << "------------------------------" << endl;
    crewEngineer.assignToShip(clonedShip);
    crewEngineer.displayInfo();
    cout << "'" << mySharedShip->getName() << "' ref count after Engineer reassigned: " << mySharedShip.use_count() << endl;
    cout << "'" << clonedShip->getName() << "' ref count after Engineer boarded: " << clonedShip.use_count() << endl;
    cout << "------------- END ------------" << endl;
    mySharedShip.reset();
    clonedShip.reset();

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}