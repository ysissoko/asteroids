#include <src/asteroids/asteroid.hpp>
#include <cmath>
#include <spdlog/spdlog.h>

#include <src/game/game.hpp>

using json = nlohmann::json;

Asteroid::Asteroid(std::shared_ptr<Generator> gen, const sf::Vector2f &initial_pos, float speed, float angle, unsigned int life, std::shared_ptr<HUD> hud, std::shared_ptr<SoundPlayer> sp) : GameObject(ObjectType::ASTEROID, "asteroid"), hud_{hud}, gen_{gen}, angle_{angle}, speed_{speed}, life_{life}, initial_pos_{initial_pos}, sp_{sp}
{
    Init();
}

void Asteroid::UpdateConvexShapePoints(const std::vector<sf::Vector2f> &rand_points) const
{
    auto index = 0;

    shape_->setPointCount(rand_points.size());

    for (auto point : rand_points)
    {
        shape_->setPoint(index, point);
        index++;
    }
}

void Asteroid::Init()
{
    shape_ = std::make_shared<sf::ConvexShape>();

    UpdateConvexShapePoints(gen_->GeneratePoints(life_));

    shape_->setPosition(initial_pos_);
    shape_->setOutlineColor(sf::Color::White);
    shape_->setFillColor(sf::Color::Transparent);
    shape_->setOutlineThickness(1);

    set_shape(shape_);
}

void Asteroid::Update(float elapsed_time)
{
    shape_->move(-sf::Vector2f(speed_ * elapsed_time * std::cos(angle_), speed_ * elapsed_time * std::sin(angle_)));

    sf::Vector2f pos = shape_->getPosition();

    auto width = shape_->getGlobalBounds().width;
    auto height = shape_->getGlobalBounds().height;

    const unsigned int w_width = Game::config["window"]["width"].get<unsigned int>();
    const unsigned int w_height = Game::config["window"]["height"].get<unsigned int>();

    if (pos.x >= w_width)
        pos.x = 0;
    if (pos.x <= -width)
        pos.x = w_width;
    if (pos.y <= -height)
        pos.y = w_height;
    if (pos.y >= w_height)
        pos.y = -height;

    shape_->setPosition(pos);
}

void Asteroid::CollideWith(std::shared_ptr<GameObject> obj)
{
    if (obj->get_type() == ObjectType::BULLET)
    {
        spdlog::debug("bullet collide with object id: {}", obj->get_id());
        life_--;
        sp_->PlaySound("destruction");
        hud_->IncreaseScore();
        gen_->ExplodeAsteroid(obj->get_id(), shared_from_this());
    }
}
