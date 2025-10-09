#pragma once

#include "Common.h"

class SoundSystem{
private:
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> musics;
    bool isMusicPlaying = false;
    float masterVolume = 1.0f; // Volume range from 0.0f to 1.0f
public:
    void LoadSFX(const std::string& name, const std::string& filepath);
    void LoadMusic(const std::string& name, const std::string& filepath);
    void PlaySFX(const std::string& name);
    void PlayMusic(const std::string& name, bool loop = true);
    void Update();
    void StopMusic();
    void SetVolume(float volume); // Set master volume
    void CleanUp();
};