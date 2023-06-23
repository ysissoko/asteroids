#include <src/asteroids/asteroid.hpp>
#include <cmath>
#include <spdlog/spdlog.h>

Asteroid::Asteroid(std::shared_ptr<Generator> gen, const sf::Vector2f &initial_pos, float speed, float angle, unsigned int life) : GameObject(ObjectType::ASTEROID, "asteroid"), gen_{gen}, angle_{angle}, speed_{speed}, life_{life}, initial_pos_{initial_pos}
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

    if (pos.x >= 800)
        pos.x = 0;
    if (pos.x <= -width)
        pos.x = 800;
    if (pos.y <= -height)
        pos.y = 600;
    if (pos.y >= 600)
        pos.y = -height;

    shape_->setPosition(pos);
}

void Asteroid::CollideWith(std::shared_ptr<GameObject> obj)
{
    if (obj->get_type() == ObjectType::BULLET)
    {
        spdlog::debug("bullet collide with object id: {}", obj->get_id());
        life_--;
        gen_->ExplodeAsteroid(obj->get_id(), shared_from_this());
    }
}
