#include "SoundManager.hpp"
#include <iostream>

SoundManager& SoundManager::GetInstance()
{
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager()
{
    ma_result result = ma_engine_init(NULL, &m_engine);
    if (result != MA_SUCCESS) {
        std::cout << "Error: Failed to initialize audio engine!" << std::endl;
    }
}

SoundManager::~SoundManager()
{
    ma_engine_uninit(&m_engine);
}

void SoundManager::AddSound(const std::string& name, const std::string& filepath)
{
    m_soundPaths[name] = filepath;
}

void SoundManager::Play(const std::string& name)
{
    if (m_soundPaths.find(name) == m_soundPaths.end())
    {
        std::cout << "SoundManager Error: Sound not found!" << std::endl;
        return;
    }

    ma_engine_play_sound(&m_engine, m_soundPaths[name].c_str(), NULL);
}

void SoundManager::SetVolume(float volume)
{
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;
    ma_engine_set_volume(&m_engine, volume);
}
