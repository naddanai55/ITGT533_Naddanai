#include "Crew.hpp"
#include "SpaceShip.hpp" // Include the full definition of SpaceShip here
                       // because we need to call methods like assignedShip->getName()

// Constructor
Crew::Crew(std::string r, std::shared_ptr<SpaceShip> ship)
    : role(r), assignedShip(ship) { // The shared_ptr is copied, incrementing its reference count
    std::cout << "Crew member '" << role << "' created. ";
    if (assignedShip) {
        std::cout << "Assigned to ship: " << assignedShip->getName() << ".";
    }
    else {
        std::cout << "Not yet assigned to a ship.";
    }
    std::cout << std::endl;
}

// Display crew member's information
void Crew::displayInfo() const {
    std::cout << "Crew Role: " << role;
    if (assignedShip) {
        // We need SpaceShip::getName() to be available.
        // Ensure SpaceShip.h is included and SpaceShip has a public getName() const method.
        std::cout << ", Assigned to Ship: '" << assignedShip->getName() << "'";
        std::cout << " (Ship Ref Count: " << assignedShip.use_count() << ")"; // Shows how many shared_ptrs point to the ship
    }
    else {
        std::cout << ", Currently unassigned.";
    }
    std::cout << std::endl;
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
