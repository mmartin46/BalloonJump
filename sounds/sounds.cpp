#include "sounds.h"


void AudioHandler::volume_check(float volume)
{
    if ((volume < music_settings::VOLUME_MIN) || (volume > music_settings::VOLUME_MAX))
    {
        std::cerr << "AudioHandler.is_valid_volume() -> Unacceptable volume." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void AudioHandler::play_sound(const char *file, float volume)
{
    volume_check(volume);
    static sf::SoundBuffer soundBuff;
    static sf::Sound sound;
    try
    {
        soundBuff.loadFromFile(file);
        sound.setBuffer(soundBuff);
        sound.setVolume(volume);
        sound.play();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AudioHandler::play_music(const char *file, float volume)
{
    volume_check(volume);
    auto *singleton = &get_instance();
    try
    {
        singleton->background_music.openFromFile(file);
        singleton->background_music.setVolume(volume);
        singleton->background_music.setLoop(true);
        singleton->background_music.play();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AudioHandler::stop_music()
{
    auto *singleton = &get_instance();
    singleton->background_music.stop();
}