
#include "src/asteroids/generator.hpp"
#include "src/asteroids/asteroid.hpp"
#include "src/common/common.hpp"
#include "src/game/game.hpp"

#include <spdlog/spdlog.h>

Generator::Generator(std::shared_ptr<GameState> gs, json generator_config, std::shared_ptr<HUD> hud, std::shared_ptr<SoundPlayer> sp) : gs_(gs), gen_(rd()), hud_{hud}, sp_{sp}
{
    try
    {
        pos_ = sf::Vector2f(generator_config["pos"]["x"], generator_config["pos"]["y"]);
        angle_range_ = std::make_pair<float, float>(generator_config["angle"]["min"], generator_config["angle"]["max"]);
        speed_range_ = std::make_pair<float, float>(generator_config["asteroid"]["speed"]["min"], generator_config["asteroid"]["speed"]["max"]);
        life_range_ = std::make_pair<unsigned int, unsigned int>(generator_config["asteroid"]["life"]["min"], generator_config["asteroid"]["life"]["max"]);
        max_asteroids_ = generator_config["asteroid"]["maxCount"];
        freq_ = generator_config["freq"];
        shape_size_ = generator_config["asteroid"]["size"];
        peak_range_ = std::make_pair<float, float>(generator_config["asteroid"]["peak"]["min"], generator_config["asteroid"]["peak"]["max"]);
    }
    catch (std::exception e)
    {
        spdlog::error("Error loading configuration params {}", e.what());
    }
}

void Generator::Update(float elapsed_time)
{
    elapsed_time_ += elapsed_time;

    spdlog::debug("generated asteroids count: {}", gs_->GetObjectCount(ObjectType::ASTEROID));
    
    if (elapsed_time_ >= freq_ && gs_->GetObjectCount(ObjectType::ASTEROID) < max_asteroids_)
    {
        spdlog::debug("generate new asteroid");
        std::uniform_real_distribution<> dis_angle(angle_range_.first, angle_range_.second);
        std::uniform_real_distribution<> dis_speed(speed_range_.first, speed_range_.second);
        std::uniform_int_distribution<> dis_life(life_range_.first, life_range_.second); // random life generation for a polygon

        GenerateAsteroid(dis_life(gen_), dis_speed(gen_), deg2rad(dis_angle(gen_)), pos_);
        elapsed_time_ = 0;
    }
}

void Generator::GenerateAsteroid(const int life, const float speed, const float trajectory_angle, const sf::Vector2f &initial_pos)
{
    gs_->AddObject(std::make_shared<Asteroid>(shared_from_this(), initial_pos, speed, trajectory_angle, life, hud_, sp_));
}

std::vector<sf::Vector2f> Generator::GeneratePoints(const int life)
{
    auto angle = 0;
    std::vector<sf::Vector2f> points;
    std::uniform_real_distribution<> dis_scale_factor(peak_range_.first, peak_range_.second); // random convex shape generation

    while (angle != 360)
    {
        auto scale_factor = dis_scale_factor(gen_);
        points.push_back(sf::Vector2f(life * std::cos(deg2rad(angle)) * scale_factor * shape_size_, life * std::sin(deg2rad(angle)) * scale_factor * shape_size_));
        angle += 45;
    }

    return points;
}

void Generator::ExplodeAsteroid(uint64_t bullet_id, std::shared_ptr<Asteroid> asteroid)
{
    if (asteroid->get_life() <= 0)
    {
        spdlog::debug("dispose bullet id {}", bullet_id);
        gs_->RemoveObject(asteroid);
    }
    else
    {
        // divide asteroid
        asteroid->UpdateConvexShapePoints(GeneratePoints(asteroid->get_life()));
        GenerateAsteroid(asteroid->get_life(), asteroid->get_speed(), -asteroid->get_angle(), asteroid->get_position());
    }

    gs_->RemoveObject(bullet_id);
}
