#pragma once

#include <GL/glew.h>
#include <string>

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};