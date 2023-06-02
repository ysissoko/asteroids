#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string_view>
#include <filesystem>

class SoundNotFoundException : public std::exception
{
private:
    std::string_view sound_name_;

public:
    explicit SoundNotFoundException(const std::string_view &sound_name) : std::exception(), sound_name_(sound_name)
    {
    }
    const char *what() const throw() override
    {
        std::stringstream sstr{""};
        sstr << "Sound " << sound_name_ << " not found";
        return sstr.str().c_str();
    }
};

class SoundPlayer
{
private:
    std::unordered_map<std::string_view, sf::SoundBuffer> sounds;

public:
    SoundPlayer() = default;
    ~SoundPlayer() = default;

    void PlaySound(std::string_view name);
    void LoadSound(std::string_view name, const std::filesystem::path &path);
};

#endif
