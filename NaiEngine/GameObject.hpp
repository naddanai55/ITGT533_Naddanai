#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

// Forward-declare the Mesh class. This is a good practice that can speed up
// compilation, as we don't need the full definition of Mesh here, just that it exists.
class Mesh;

// Declare the global ID counter as 'extern'.
// This tells the compiler, "This variable exists somewhere, but it's not defined in this file."
// The actual variable will be defined in GameObject.cpp.
extern unsigned int gameObjectIDCounter;

class GameObject
{
public:
    unsigned int id;
    std::string name;

    // Transform properties
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    // A pointer to the mesh data.
    std::shared_ptr<Mesh> mesh;

    // Constructor declaration
    GameObject(std::string name, std::shared_ptr<Mesh> mesh);

    // Method declaration
    glm::mat4 getModelMatrix() const;
};