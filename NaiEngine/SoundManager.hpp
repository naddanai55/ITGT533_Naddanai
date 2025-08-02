#pragma once

#include "miniaudio.h"
#include <string>
#include <map>

class SoundManager
{
public:

    static SoundManager& GetInstance();
    void AddSound(const std::string& name, const std::string& filepath);
    void Play(const std::string& name);
    void SetVolume(float volume);

private:
    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    ma_engine m_engine;
    std::map<std::string, std::string> m_soundPaths;
};

