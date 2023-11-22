#pragma once

#include <unordered_map>
#include <iostream>
#include <SFML/Audio.hpp>

using std::unordered_map;
using std::make_unique;
using std::unique_ptr;
using std::string;

namespace music_settings
{
    constexpr int VOLUME_MAX = 100;
    constexpr int VOLUME_MIN = 0;
}

class AudioHandler
{
    private:
        unordered_map<string, unique_ptr<sf::Music>> tracks;

        unordered_map<string, sf::SoundBuffer> sound_buffers;
        unordered_map<string, sf::Sound> sounds;
        
    public:
        AudioHandler() {};

        void load_track(const string &custom_name, const string &file_path);
        void play_track(const string &name);
        void pause_track(const string &name);
        void stop_track(const string &name);
        void stop_music();

        void set_volume(const string &name, float volume);


        // FIXME: Needs to be implemented
        void load_sound(const string &custom_name, const string &file_path);
        void play_sound(const string &name);
        void pause_sound(const string &name);
        void stop_sound();
};

void AudioHandler::stop_music()
{
    for (auto &it : tracks)
    {
        it.second->stop();
    }
}

void AudioHandler::load_track(const string &custom_name, const string &file_path)
{
    try
    {
        auto track = make_unique<sf::Music>();
        if (track->openFromFile(file_path))
        {
            // Enforces ownership, to prevent issues with copying.
            tracks.at(custom_name) = std::move(track);
        }
        else
        {
            throw std::runtime_error("AudioHandler::load_track(): Invalid Path \"" + file_path + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::load_track(): " << e.what() << '\n';
    }
    

}
void AudioHandler::play_track(const string &name)
{
    try
    {
        // Try to play the track
        auto it = tracks.find(name);
        if (it != tracks.end())
        {
            it->second->play();
        }
        else
        {
            throw std::runtime_error("AudioHandler::play_track(): Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::play_track(): " << e.what() << '\n';
    }
    
}

void AudioHandler::pause_track(const string &name)
{
    try
    {
        // Try to pause the track
        auto it = tracks.find(name);
        if (it != tracks.end())
        {
            it->second->pause();
        }
        else
        {
            throw std::runtime_error("AudioHandler::pause_track(): Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::pause_track(): " << e.what() << '\n';
    }
        
}

void AudioHandler::stop_track(const string &name)
{
    try
    {
        // Try to stop the track
        auto it = tracks.find(name);
        if (it != tracks.end())
        {
            it->second->stop();
        }
        else
        {
            throw std::runtime_error("AudioHandler::pause_track(): Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::pause_track(): " << e.what() << '\n';
    }
        
}

void AudioHandler::set_volume(const string &name, float volume)
{
    try
    {
        auto it = tracks.find(name);
        if (it != tracks.end())
        {
            if ((volume <= music_settings::VOLUME_MAX) &&
                (volume >= music_settings::VOLUME_MIN))
            {
                it->second->setVolume(volume);
            }
            else
            {
                throw std::runtime_error("AudioHandler::set_volume(): Invalid Volume with \"" + name + "\"");
            }
        }
        else
        {
            throw std::runtime_error("AudioHandler::set_volume(): Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::set_volume(): " << e.what() << '\n';
    }
}