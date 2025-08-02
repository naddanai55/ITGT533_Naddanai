#include "Mesh3d.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    this->vertices = vertices;
    this->indices = indices;
    setupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh Mesh::CreateCube(float size)
{
    float s = size / 2.0f;

    std::vector<Vertex> vertices = {
        // Positions            // Colors         // TexCoords    // Normals
        // Back face (-Z)
        Vertex({-s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(0.0f,  0.0f, -1.0f)}),
        Vertex({ s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(0.0f,  0.0f, -1.0f)}),
        Vertex({ s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(0.0f,  0.0f, -1.0f)}),
        Vertex({-s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(0.0f,  0.0f, -1.0f)}),

        // Front face (+Z)
        Vertex({-s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(0.0f,  0.0f, 1.0f)}),
        Vertex({ s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(0.0f,  0.0f, 1.0f)}),
        Vertex({ s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(0.0f,  0.0f, 1.0f)}),
        Vertex({-s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(0.0f,  0.0f, 1.0f)}),

        // Left face (-X)
        Vertex({-s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(-1.0f,  0.0f,  0.0f)}),
        Vertex({-s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(-1.0f,  0.0f,  0.0f)}),
        Vertex({-s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(-1.0f,  0.0f,  0.0f)}),
        Vertex({-s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(-1.0f,  0.0f,  0.0f)}),

        // Right face (+X)
        Vertex({ s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(1.0f,  0.0f,  0.0f)}),
        Vertex({ s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(1.0f,  0.0f,  0.0f)}),
        Vertex({ s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(1.0f,  0.0f,  0.0f)}),
        Vertex({ s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(1.0f,  0.0f,  0.0f)}),

        // Bottom face (-Y)
        Vertex({-s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(0.0f, -1.0f,  0.0f)}),
        Vertex({ s, -s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(0.0f, -1.0f,  0.0f)}),
        Vertex({ s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(0.0f, -1.0f,  0.0f)}),
        Vertex({-s, -s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(0.0f, -1.0f,  0.0f)}),

        // Top face (+Y)
        Vertex({-s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 1.0f)}, {glm::vec3(0.0f,  1.0f,  0.0f)}),
        Vertex({-s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(0.0f, 0.0f)}, {glm::vec3(0.0f,  1.0f,  0.0f)}),
        Vertex({ s,  s,  s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 0.0f)}, {glm::vec3(0.0f,  1.0f,  0.0f)}),
        Vertex({ s,  s, -s}, {glm::vec3(1.0f)}, {glm::vec2(1.0f, 1.0f)}, {glm::vec3(0.0f,  1.0f,  0.0f)})
    };

    std::vector<unsigned int> indices = {
         0,  1,  2,      0,  3,  1, // Back
         4,  5,  6,      4,  6,  7, // Front
         8,  9, 10,      8, 10, 11, // Left
        12, 13, 14,     12, 15, 13, // Right
        16, 17, 18,     16, 18, 19, // Bottom
        20, 21, 22,     20, 22, 23  // Top
    };

    return Mesh(vertices, indices);
}