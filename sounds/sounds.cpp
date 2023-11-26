#include "sounds.h"

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
void AudioHandler::play_track(const string &name, float volume)
{
    try
    {
        // Try to play the track
        auto it = tracks.find(name);
        if (it != tracks.end())
        {
            it->second->setVolume(volume);
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


void AudioHandler::load_sound(const string &custom_name, const string &file_path)
{
    try
    {
        auto buffer = make_unique<sf::SoundBuffer>();
        if (buffer->loadFromFile(file_path))
        {
            sound_buffers.insert(std::make_pair(custom_name, std::move(buffer)));
        }
        else
        {
            throw std::runtime_error("Invalid Path \"" + file_path + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::load_sound(): " << e.what() << '\n';
    }
    
}
void AudioHandler::play_sound(const string &name, float volume)
{
    try
    {
        auto buffer_it = sound_buffers.find(name);
        if (buffer_it != sound_buffers.end())
        {

            auto &buffer = *(buffer_it->second);

            // Setup the buffer
            sf::Sound sound;
            sound.setBuffer(buffer);

            sound.setVolume(volume);
            sound.play();

            sounds[name] = std::move(sound);
        }
        else
        {
            throw std::runtime_error("Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::play_sound(): " << e.what() << '\n';
    }
    
}
void AudioHandler::pause_sound(const string &name)
{
    try
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            it->second.pause();
        }
        else
        {
            throw std::runtime_error("Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::pause_sound(): " << e.what() << '\n';
    }
    
}
void AudioHandler::stop_sound(const string &name)
{
    try
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            it->second.stop();
        }
        else
        {
            throw std::runtime_error(": Invalid Name \"" + name + "\"");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "AudioHandler::stop_sound(): " << e.what() << '\n';
    }
}

void AudioHandler::print_sounds()
{
    const int BAR_WIDTH = 10;
    std::cout << "Sounds" << std::endl;
    for (int i = 0; i < BAR_WIDTH; ++i)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (auto &it : sounds)
    {
        std::cout << it.first << " ";
        switch (it.second.getStatus())
        {
            case sf::Sound::Playing:
                std::cout << "(playing)";
                break;
            case sf::Sound::Paused:
                std::cout << "(paused)";
                break;
            case sf::Sound::Stopped:
                std::cout << "(stopped)";
                break;
            default:
                std::cout << "(unknown debug?)";
                break;
        }
        std::cout << std::endl;
    }
}
