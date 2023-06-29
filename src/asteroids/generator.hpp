#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>

#include <src/game/game-state.hpp>
#include <src/ui/hud.hpp>
#include <src/renderer/soundplayer.hpp>

#include <SFML/System/Clock.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Asteroid;

class Generator : public std::enable_shared_from_this<Generator>
{
public:
    Generator(std::shared_ptr<GameState> gs, nlohmann::json config, std::shared_ptr<HUD> hud, std::shared_ptr<SoundPlayer> sp);
    ~Generator() = default;

    void Update(float);
    sf::Vector2f get_position() const { return pos_; }

    void ExplodeAsteroid(uint64_t bullet_id, std::shared_ptr<Asteroid> asteroid);
    void GenerateAsteroid(const int life, const float speed, const float trajectory_angle, const sf::Vector2f &);
    std::vector<sf::Vector2f> GeneratePoints(const int);

private:
    sf::Vector2f pos_;
    sf::Vector2f initial_pos_;
    std::pair<float, float> angle_range_;
    std::pair<float, float> speed_range_;
    std::pair<float, float> peak_range_;
    unsigned int max_asteroids_;
    std::pair<unsigned int, unsigned int> life_range_;
    std::shared_ptr<GameState> gs_{nullptr};
    float freq_{1};
    float elapsed_time_{0};
    unsigned int shape_size_{0};
    std::shared_ptr<HUD> hud_{nullptr};
    std::shared_ptr<SoundPlayer> sp_{nullptr};

    std::random_device rd;
    std::mt19937 gen_;
};

#endif
