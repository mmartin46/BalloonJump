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
}

class AudioHandler
{
    private:
        unordered_map<string, unique_ptr<sf::Music>> tracks;

        unordered_map<string, unique_ptr<sf::SoundBuffer>> sound_buffers;
        unordered_map<string, sf::Sound> sounds;
        
    public:
        // Returns one instance of the AudioHandler
        static AudioHandler& get_instance()
        {
            static AudioHandler instance;
            return instance;
        }

        AudioHandler() = default;

        void load_track(const string &custom_name, const string &file_path);
        void play_track(const string &name, float volume);
        void pause_track(const string &name);
        void stop_track(const string &name);
        void stop_music();

        void set_volume(const string &name, float volume=music_settings::DEFAULT_VOLUME);


        void load_sound(const string &custom_name, const string &file_path);
        void play_sound(const string &name, float volume=music_settings::DEFAULT_VOLUME);
        void pause_sound(const string &name);
        void stop_sound(const string &name);
};

#endif