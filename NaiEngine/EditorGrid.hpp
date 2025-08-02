#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class EditorGrid
{
public:
    EditorGrid(float size, int divisions);
    ~EditorGrid();
    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    void setupBuffers();
    unsigned int m_LineShaderProgram;
    unsigned int m_GridVAO, m_GridVBO;
    int m_GridVertexCount;
    unsigned int m_AxisVAO, m_AxisVBO;
};