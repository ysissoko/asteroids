#include <src/renderer/soundplayer.hpp>
#include <future>
#include <iostream>
#include <spdlog/spdlog.h>

void SoundPlayer::PlaySound(std::string_view name)
{

    auto future = std::async(std::launch::async, [&name, this]()
                             {  
                    auto it = this->sounds.find(name);
                    if (it == this->sounds.end())
                        throw SoundNotFoundException(name);
                    spdlog::debug("Playing sound {}", it->first);
                    sf::Sound sound;
                    sound.setBuffer(it->second);
                    sound.setVolume(100.f);
                    sound.play(); });

    try
    {
        future.get();
    }
    catch (const SoundNotFoundException &ex)
    {
        spdlog::error("{}", ex.what());
    }
}

void SoundPlayer::LoadSound(std::string_view name, const std::filesystem::path &path)
{
    sf::SoundBuffer sb;

    if (!sb.loadFromFile(path))
        throw SoundNotFoundException(path.generic_string());

    this->sounds.try_emplace(name, sb);
}
