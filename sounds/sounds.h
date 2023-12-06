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

namespace music_settings
{
    constexpr int VOLUME_MAX = 100;
    constexpr int VOLUME_MIN = 0;
    constexpr float DEFAULT_VOLUME = 30;

    namespace sound_file_paths
    {
        constexpr const char* PLAYER_JUMP_SOUND = "entities//jump.wav";
        constexpr const char* COIN_COLLECT_SOUND = "sounds//coin_collect.wav";
        constexpr const char* ENEMY_STOMP_SOUND = "sounds//enemy_stomp.wav";
    }
}

class AudioHandler
{
    private:
        AudioHandler() = default;
    public:
        // Returns one instance of the AudioHandler
        static AudioHandler& get_instance()
        {
            static AudioHandler instance;
            return instance;
        }
        static void play_sound(const char*, float volume=music_settings::DEFAULT_VOLUME);
};




#endif