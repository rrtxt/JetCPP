#include "SoundSystem.h"

void SoundSystem::LoadSFX(const std::string& name, const std::string& filepath) {
    Sound sound = LoadSound(filepath.c_str());
    sounds[name] = sound;
}

void SoundSystem::LoadMusic(const std::string& name, const std::string& filepath) {
    Music music = LoadMusicStream(filepath.c_str());
    musics[name] = music;
}

void SoundSystem::PlaySFX(const std::string& name) {
    std::cout << "Attempting to play SFX: " << name << std::endl;
    if (sounds.find(name) != sounds.end()) {
        SetSoundVolume(sounds[name], masterVolume); // Volume range from 0 to 100
        std::cout << "Playing SFX: " << name << " at volume: " << (masterVolume * 100) << "%" << std::endl;
        PlaySound(sounds[name]);
    }
}

void SoundSystem::PlayMusic(const std::string& name, bool loop) {
    if (musics.find(name) != musics.end()) {
        if (isMusicPlaying) {
            StopMusicStream(musics[name]);
        }
        SetMusicVolume(musics[name], masterVolume * 100); // Volume range from 0 to 100
        PlayMusicStream(musics[name]);
        isMusicPlaying = true; 
    }
}

void SoundSystem::Update() {
    for (auto& [name, music] : musics) {
        UpdateMusicStream(music);
    }
}

void SoundSystem::StopMusic() {
    for (auto& [name, music] : musics) {
        StopMusicStream(music);
    }
    isMusicPlaying = false;
}

void SoundSystem::SetVolume(float volume) {
    masterVolume = std::clamp(volume, 0.0f, 1.0f);
    std::cout << "Master volume set to: " << (masterVolume * 100) << "%" << std::endl;
    SetMasterVolume(masterVolume * 100); // Volume range from 0 to 100
    // for (auto& [name, sound] : sounds) {
    //     SetSoundVolume(sound, masterVolume * 100); // Volume range from 0 to 100
    // }
    // for (auto& [name, music] : musics) {
    //     SetMusicVolume(music, masterVolume * 100); // Volume range from 0 to 100
    // }
}

void SoundSystem::UnloadSFX(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        UnloadSound(sounds[name]);
        sounds.erase(name);
    }
}

void SoundSystem::UnloadMusic(const std::string& name) {
    if (musics.find(name) != musics.end()) {
        UnloadMusicStream(musics[name]);
        musics.erase(name);
    }
}

void SoundSystem::CleanUp() {
    for (auto& [name, sound] : sounds) {
        UnloadSound(sound);
    }
    sounds.clear();
    
    for (auto& [name, music] : musics) {
        UnloadMusicStream(music);
    }
    musics.clear();
}