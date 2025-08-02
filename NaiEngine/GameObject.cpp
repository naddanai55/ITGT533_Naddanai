#include "GameObject.hpp" // Include the header to get the class declaration

#include "Mesh3d.hpp" // We need the full Mesh definition here
#include <glm/gtc/matrix_transform.hpp> // For glm::translate, glm::rotate, glm::scale

// Define and initialize the global static counter here.
// This is the one and only place in your entire project where this variable is created.
unsigned int gameObjectIDCounter = 0;

GameObject::GameObject(std::string name, std::shared_ptr<Mesh> mesh)
    : name(name), mesh(mesh)
{
    id = gameObjectIDCounter++;
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}

glm::mat4 GameObject::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}