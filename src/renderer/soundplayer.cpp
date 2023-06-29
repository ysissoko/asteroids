#include <src/renderer/soundplayer.hpp>
#include <future>
#include <iostream>
#include <spdlog/spdlog.h>

void SoundPlayer::PlaySound(std::string_view name)
{
    auto it = this->sounds.find(name);
    if (it == this->sounds.end())
        throw SoundNotFoundException(name);
    spdlog::debug("Playing sound {}", it->first);
    sf::Sound sound;
    sound.setBuffer(it->second);
    // sound.setVolume(100.f);
    if (sound.getStatus() != sf::SoundSource::Playing)
        sound.play();
}

void SoundPlayer::LoadSound(std::string_view name, const std::filesystem::path &path)
{
    sf::SoundBuffer sb;

    if (!sb.loadFromFile(path))
        throw SoundNotFoundException(path.generic_string());

    this->sounds.try_emplace(name, sb);
}
