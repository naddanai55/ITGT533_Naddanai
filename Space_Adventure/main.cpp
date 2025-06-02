#include <iostream>
#include <cassert>
#include "Weapon.hpp"
#include "Plasma.hpp"
#include "Missile.hpp"
#include "Laser.hpp"
#include "SpaceShip.hpp"
#include "Crew.hpp"

using namespace std;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SpaceShip myShip("USSEnterprise");
    myShip.addWeapon(make_unique<Laser>(10));
    myShip.addWeapon(make_unique<Plasma>(20));
    myShip.addWeapon(make_unique<Missile>(30));
    myShip.fireAllWeapons();
    cout << "---Ship Status---" << endl;
    cout << myShip.getName() << endl;
    cout << myShip.getHealth() << endl;

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}