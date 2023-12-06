#include "sounds.h"

void AudioHandler::play_sound(const char *file, float volume)
{
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