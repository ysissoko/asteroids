#include <src/vehicle/bullet.hpp>

Bullet::Bullet(std::shared_ptr<Vehicle> veh) : GameObject("bullet")
{
    bullet_heading_ = veh->get_heading_angle();
    InitDrawable(veh);
}

void Bullet::InitDrawable(std::shared_ptr<Vehicle> veh)
{
    bullet_shape_ = std::make_shared<sf::CircleShape>(4);
    bullet_shape_->setOrigin(bullet_shape_->getRadius() / 2, bullet_shape_->getRadius() / 2);

    bullet_shape_->setPosition(veh->get_shape()->getPosition());
    bullet_shape_->setFillColor(sf::Color::Yellow);

    bullet_shape_->move(-sf::Vector2f(veh->get_shape()->getRadius() * std::cos(bullet_heading_), veh->get_shape()->getRadius() * std::sin(bullet_heading_)));

    set_drawable(bullet_shape_);
}

void Bullet::Update(float elapsed_time)
{
    bullet_shape_->move(-sf::Vector2f(kSpeed * elapsed_time * std::cos(bullet_heading_), kSpeed * elapsed_time * std::sin(bullet_heading_)));
}
