#include "Mesh.h"

// Constructor: takes vertex and index data and calls setupMesh to create GPU buffers.
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    this->vertices = vertices;
    this->indices = indices;

    setupMesh();
}

// Destructor: cleans up the GPU resources.
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// Configures the VAO, VBO, and EBO and sets up vertex attribute pointers.
void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex Position Attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

    // Vertex Color Attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    // Vertex Texture Coordinate Attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

    glBindVertexArray(0);
}

// Renders the mesh.
void Mesh::Draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh Mesh::CreateCube(float size) {
    float s = size / 2.0f; // half-size

    std::vector<Vertex> vertices = {
        // Position            // Color
        {glm::vec3(-s, -s,  s), glm::vec3(1.0f, 0.0f, 0.0f)}, // 0: Front Bottom Left (Red)
        {glm::vec3(s, -s,  s), glm::vec3(0.0f, 1.0f, 0.0f)}, // 1: Front Bottom Right (Green)
        {glm::vec3(s,  s,  s), glm::vec3(0.0f, 0.0f, 1.0f)}, // 2: Front Top Right (Blue)
        {glm::vec3(-s,  s,  s), glm::vec3(1.0f, 1.0f, 0.0f)}, // 3: Front Top Left (Yellow)

        {glm::vec3(-s, -s, -s), glm::vec3(1.0f, 0.0f, 1.0f)}, // 4: Back Bottom Left (Magenta)
        {glm::vec3(s, -s, -s), glm::vec3(0.0f, 1.0f, 1.0f)}, // 5: Back Bottom Right (Cyan)
        {glm::vec3(s,  s, -s), glm::vec3(1.0f, 1.0f, 1.0f)}, // 6: Back Top Right (White)
        {glm::vec3(-s,  s, -s), glm::vec3(0.0f, 0.0f, 0.0f)}, // 7: Back Top Left (Black)
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Back face
        7, 6, 5, 5, 4, 7,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };

    return Mesh(vertices, indices);
}
