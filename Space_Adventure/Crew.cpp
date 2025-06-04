#include "Crew.hpp"
#include "SpaceShip.hpp" 
#include <iostream>

// Constructor
Crew::Crew(std::string r, std::shared_ptr<SpaceShip> ship) : role(r), assignedShip(ship) 
{
    cout << "Crew member '" << role << "' created. ";
    if (assignedShip) 
    {
        cout << "Assigned to ship: " << assignedShip->getName() << "." << endl;
    }
    else
    {
        cout << "Not yet assigned to a ship." << endl;
    }
}

// Display crew member's information
void Crew::displayInfo() const 
{
    cout << "Crew Role: " << role;
    if (assignedShip) 
    {
        cout << ", Assigned to Ship: '" << assignedShip->getName() << "'";
        cout << " (Ship Ref Count: " << assignedShip.use_count() << ")" << endl; // Shows how many shared_ptrs point to the ship
    }
    else 
    {
        cout << ", Currently unassigned." << endl;
    }
    cout << endl;
}

// Assign or re-assign the crew member to a ship
void Crew::assignToShip(std::shared_ptr<SpaceShip> ship) {
    if (assignedShip) {
        std::cout << role << " is leaving ship '" << assignedShip->getName() << "'." << std::endl;
    }
    assignedShip = ship; // Assigns the new shared_ptr.
    // Old ship's ref count decreases (if assignedShip was not null).
    // New ship's ref count increases (if ship is not null).
    if (assignedShip) {
        std::cout << role << " has been assigned to ship '" << assignedShip->getName() << "'." << std::endl;
    }
    else {
        std::cout << role << " is now unassigned." << std::endl;
    }
}

// Check if the crew member is assigned to any ship
bool Crew::isAssigned() const {
    return assignedShip != nullptr; // or simply: return (bool)assignedShip;
}

// Get the role
std::string Crew::getRole() const {
    return role;
}

// Get a const reference to the shared_ptr
const std::shared_ptr<SpaceShip>& Crew::getAssignedShip() const {
    return assignedShip;
}

// Destructor (Example, not strictly necessary here as shared_ptr handles its resource)
// Crew::~Crew() {
//     std::cout << "Crew member '" << role << "' is off duty (destroyed).";
//     if (assignedShip) {
//         std::cout << " Was assigned to '" << assignedShip->getName() << "'.";
//         // The shared_ptr 'assignedShip' will automatically decrease the ship's reference count
//         // when this Crew object is destroyed.
//     }
//     std::cout << std::endl;
// }
