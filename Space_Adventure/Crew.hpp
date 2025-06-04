#pragma once
#include <iostream>
#include "SpaceShip.hpp"

using namespace std;

class Crew
{
private:
    string role;
    shared_ptr<SpaceShip> assignedShip;

public:
    // Constructor
    Crew(string r, shared_ptr<SpaceShip> ship = nullptr); // Default ship to nullptr

    void displayInfo() const;

    void assignToShip(shared_ptr<SpaceShip> ship);

    bool isAssigned() const;

    string getRole() const;

    const shared_ptr<SpaceShip>& getAssignedShip() const;
};
