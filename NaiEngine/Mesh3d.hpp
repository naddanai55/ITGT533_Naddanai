#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TexCoord;
    glm::vec3 Normal;

    Vertex(glm::vec3 pos, glm::vec3 color = glm::vec3(1.0f), glm::vec2 texCoord = glm::vec2(0.0f), glm::vec3 normal = glm::vec3(0.0f))
        : Position(pos), Color(color), TexCoord(texCoord), Normal(normal) {}
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;

    static Mesh CreateCube(float size = 1.0f);

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};