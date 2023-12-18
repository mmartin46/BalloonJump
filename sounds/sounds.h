#ifndef SOUNDS_H
#define SOUNDS_H
#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>

using std::unordered_map;
using std::make_unique;
using std::unique_ptr;
using std::string;

/*
Contains music settings
*/
namespace music_settings
{
    constexpr int VOLUME_MAX = 100;
    constexpr int VOLUME_MIN = 0;
    constexpr float DEFAULT_VOLUME = 30;
    constexpr float BACKGROUND_MUSIC_VOLUME = 15;

    // File paths for all sounds.
    namespace sound_file_paths
    {
        constexpr const char* PLAYER_JUMP_SOUND = "entities//jump.wav";
        constexpr const char* COIN_COLLECT_SOUND = "sounds//coin_collect.wav";
        constexpr const char* ENEMY_STOMP_SOUND = "sounds//enemy_stomp.wav";
    }

    // File paths for all music.
    namespace music_file_paths
    {
        constexpr const char* LEVEL_ONE_MUSIC = "sounds//bg_music_1.mp3";
    }
}

// Used to load sounds and later on music.
class AudioHandler
{
    private:
        AudioHandler() = default;
        sf::Music background_music;
    public:
        // Returns one instance of the AudioHandler
        static AudioHandler& get_instance()
        {
            static AudioHandler instance;
            return instance;
        }

        static void volume_check(float volume);
        static void play_sound(const char*, float volume=music_settings::DEFAULT_VOLUME);
        // FIXME: Add a music function
        static void play_music(const char*, float volume=music_settings::DEFAULT_VOLUME);
        static void stop_music();
};




#endif