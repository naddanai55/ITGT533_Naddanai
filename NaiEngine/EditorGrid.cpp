#include "EditorGrid.hpp"
#include <iostream>

unsigned int compileShader(unsigned int type, const char* source);
unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

struct LineVertex {
    glm::vec3 Position;
    glm::vec3 Color;
};

EditorGrid::EditorGrid(float size, int divisions)
{
    std::vector<LineVertex> gridVertices;
    glm::vec3 gridColor = glm::vec3(0.5f, 0.5f, 0.5f);
    float step = size / divisions;

    for (int i = 0; i <= divisions; ++i) {
        float pos = -size / 2.0f + i * step;

        gridVertices.push_back({ glm::vec3(-size / 2.0f, 0.0f, pos), gridColor });
        gridVertices.push_back({ glm::vec3(size / 2.0f, 0.0f, pos), gridColor });

        gridVertices.push_back({ glm::vec3(pos, 0.0f, -size / 2.0f), gridColor });
        gridVertices.push_back({ glm::vec3(pos, 0.0f,  size / 2.0f), gridColor });
    }
    m_GridVertexCount = gridVertices.size();

    std::vector<LineVertex> axisVertices = {
        // X-Axis (Red)
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(size / 2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        // Y-Axis (Green)
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(0.0f, size / 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        // Z-Axis (Blue)
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(0.0f, 0.0f, size / 2.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
    };

    extern const char* lineVertexShaderSource;
    extern const char* lineFragmentShaderSource;
    m_LineShaderProgram = createShaderProgram(lineVertexShaderSource, lineFragmentShaderSource);

    // Grid Buffers
    glGenVertexArrays(1, &m_GridVAO);
    glGenBuffers(1, &m_GridVBO);
    glBindVertexArray(m_GridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_GridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(LineVertex), gridVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, Color));
    glEnableVertexAttribArray(1);

    // Axis Buffers
    glGenVertexArrays(1, &m_AxisVAO);
    glGenBuffers(1, &m_AxisVBO);
    glBindVertexArray(m_AxisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_AxisVBO);
    glBufferData(GL_ARRAY_BUFFER, axisVertices.size() * sizeof(LineVertex), axisVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (void*)offsetof(LineVertex, Color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

EditorGrid::~EditorGrid()
{
    glDeleteProgram(m_LineShaderProgram);
    glDeleteVertexArrays(1, &m_GridVAO);
    glDeleteBuffers(1, &m_GridVBO);
    glDeleteVertexArrays(1, &m_AxisVAO);
    glDeleteBuffers(1, &m_AxisVBO);
}

void EditorGrid::Draw(const glm::mat4& view, const glm::mat4& projection)
{
    glUseProgram(m_LineShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(m_LineShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_LineShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw Grid
    glBindVertexArray(m_GridVAO);
    glDrawArrays(GL_LINES, 0, m_GridVertexCount);

    // Draw Axes
    glLineWidth(3.0f);
    glBindVertexArray(m_AxisVAO);
    glDrawArrays(GL_LINES, 0, 6);
    glLineWidth(1.0f);

    glBindVertexArray(0);
}
