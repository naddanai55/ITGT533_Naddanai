#pragma once
#include <iostream>
#include "SpaceShip.hpp"

using namespace std;

class Crew
{
    shared_ptr<SpaceShip> assignedShip;
    string role;

public:
    Crew(string r, shared_ptr<SpaceShip> ship) : role(r), assignedShip(ship) {} // Copy the shared_ptr (increments ref count)

    void displayInfo() const 
    {
        cout << "Crew Role: " << role;
        if (assignedShip) 
        {
            cout << ", Assigned to: " << assignedShip->getName();
        }
        else 
        {
            cout << ", Not assigned to any ship.";
        }
        cout << endl;
    }
};
